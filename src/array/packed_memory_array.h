#pragma once

#include <algorithm>
#include <cmath>
#include <tuple>
#include <bit>

namespace array {

static const uint8_t kInitialCapacity = 2;

template <typename ContentType>
class PackedMemoryArray {
 private:
  std::vector<ContentType> content_;
  uint32_t capacity_;
  ContentType elements_count_;
  uint32_t block_size_;
  uint32_t block_count_;
  uint32_t level_count_;

  uint32_t IntegerPartOfLog2(uint32_t n) { return std::bit_width(n) - 1; }

  /*
  * A block_id on the current level corresponds to a different block_id
  * in a different level. Given the block_id and the level_difference, this
  * function finds the block_id and the size of the block on the upper
  * level.
  */
  std::tuple<uint32_t, uint32_t> GetNormalizedBlockAndSize(
      uint32_t block_id, uint32_t level_difference) {
    return std::make_tuple(block_id / (1 << (level_difference - 1)),
                           this->block_size_ << (level_difference - 1));
  }

  double GetUpperTreshold(uint32_t level) {
    return 1.0 -
           ((1.0 - 0.5) * level) / (double)IntegerPartOfLog2(this->capacity_);
  }

  void UpdateVars(int capacity) {
    this->capacity_ = capacity;
    this->block_size_ = 1 << IntegerPartOfLog2(IntegerPartOfLog2(capacity) * 2);
    this->block_count_ = this->capacity_ / this->block_size_;
    this->level_count_ = IntegerPartOfLog2(this->block_count_);
  }

  ContentType GetMinimumFromBlock(uint32_t block_id) {
    auto starting_point = block_id * block_size_;
    auto result = std::find_if(content_.begin() + starting_point,
                               content_.begin() + starting_point + block_size_,
                               [](int value) { return value != 0; });

    return *result;
  }

  ContentType GetMaximumFromBlock(uint32_t block_id) {
    auto starting_point = block_id * block_size_;
    auto result = std::ranges::max_element(
        content_.begin() + starting_point,
        content_.begin() + starting_point + block_size_);

    return *result;
  }

  std::vector<ContentType> GetValuesInInterval(uint32_t begin,
                                               uint32_t offset) {
    std::vector<ContentType> result;
    std::ranges::copy_if(this->content_.begin() + begin,
                         this->content_.begin() + begin + offset,
                         std::back_inserter(result),
                         [](const auto& value) { return value != 0; });
    return result;
  }

  uint32_t GetValuesCountInInterval(uint32_t begin, uint32_t offset) {
    return GetValuesInInterval(begin, offset).size();
  }

  void InsertPadding(std::vector<ContentType>& vector, uint32_t target_size) {
    auto insertions = target_size - vector.size();
    if (insertions == 0)
      return;

    uint32_t interval =
        std::ceil(vector.size() / static_cast<float>(insertions));

    for (size_t i = 0; i < insertions; i++) {
      vector.insert(vector.begin() + std::min(i * interval + i, vector.size()),
                    0);
    }
  }

  uint32_t FindBlock(ContentType value, uint32_t left_block,
                     uint32_t right_block) {
    if (left_block == right_block)
      return left_block;

    uint32_t middle_block = left_block + ((right_block - left_block) / 2);
    ContentType highest_middle = GetMaximumFromBlock(middle_block);

    if (value < highest_middle)
      return FindBlock(value, 0, middle_block);

    return FindBlock(value, middle_block + 1, right_block);
  }

  uint32_t FindBlock(ContentType value) {
    if (elements_count_ == 0)
      return 0;

    uint32_t middle_block = (this->block_count_ - 1) / 2;

    if (middle_block == this->block_count_ - 1)
      return 0;

    ContentType highest_middle = GetMaximumFromBlock(middle_block);

    if (value < highest_middle)
      return FindBlock(value, 0, middle_block);

    return FindBlock(value, middle_block + 1, this->block_count_ - 1);
  }

  void Insert(ContentType value, uint32_t block_id) {
    auto initial_position = block_id * this->block_size_;

    std::vector<ContentType> auxiliary_vector;
    auxiliary_vector.reserve(this->block_size_);
    auxiliary_vector = GetValuesInInterval(initial_position, this->block_size_);

    auto position = std::ranges::lower_bound(auxiliary_vector, value);
    auxiliary_vector.insert(position, value);

    InsertPadding(auxiliary_vector, this->block_size_);

    std::copy(auxiliary_vector.begin(), auxiliary_vector.end(),
              this->content_.begin() + initial_position);
    ++this->elements_count_;
  }

  void RebalanceInterval(uint32_t block_id, uint32_t level) {
    uint32_t normalized_block_id, normalized_block_size;
    std::tie(normalized_block_id, normalized_block_size) =
        GetNormalizedBlockAndSize(block_id, level);

    auto initial_position = normalized_block_id * normalized_block_size;

    std::vector<ContentType> auxiliary_vector;
    auxiliary_vector.reserve(normalized_block_size);
    auxiliary_vector =
        GetValuesInInterval(initial_position, normalized_block_size);

    InsertPadding(auxiliary_vector, normalized_block_size);

    std::copy(auxiliary_vector.begin(), auxiliary_vector.end(),
              this->content_.begin() + initial_position);
  }

  uint32_t GetElementsInBlock(uint32_t block_id) {
    auto block_start =
        std::next(this->content_.begin(), block_id * this->block_size_);
    auto block_end = std::next(block_start, this->block_size_);

    return std::ranges::count_if(block_start, block_end,
                                 [](auto value) { return value != 0; });
  }

  bool BlockHasSpace(uint32_t block_id) {
    uint32_t elements_in_block = GetElementsInBlock(block_id);
    return elements_in_block < this->block_size_;
  }

  uint32_t OtherBlocksHaveSpace(uint32_t block_id, uint32_t level = 1) {
    if (level > this->level_count_ + 1)
      return 0;

    auto upper_threshold = GetUpperTreshold(level);
    uint32_t normalized_block_id, normalized_block_size;
    std::tie(normalized_block_id, normalized_block_size) =
        GetNormalizedBlockAndSize(block_id, level);

    auto initial_position = normalized_block_id * normalized_block_size;
    auto element_count =
        GetValuesCountInInterval(initial_position, normalized_block_size);

    auto density = element_count / static_cast<float>(normalized_block_size);
    if (density <= upper_threshold)
      return level;
    return OtherBlocksHaveSpace(block_id, level + 1);
  }

  void IncreaseSize() {
    auto new_capacity = this->capacity_ * 2;
    std::vector<ContentType> temp_content(new_capacity);
    auto density = new_capacity / static_cast<float>(this->elements_count_);

    uint32_t control = 0;
    for (uint32_t i = 0; i < this->content_.size(); ++i) {
      if (this->content_.at(i)) {
        int idx = density * (control++);
        temp_content.at(idx) = this->content_.at(i);
      }
    }

    this->content_.swap(temp_content);
    this->UpdateVars(new_capacity);
  }

 public:
  PackedMemoryArray() : capacity_(kInitialCapacity), elements_count_(0) {
    content_.resize(capacity_);
    this->UpdateVars(capacity_);
  }

  void Insert(ContentType value) {
    auto block_id = FindBlock(value);

    if (BlockHasSpace(block_id)) {
      this->Insert(value, block_id);
      return;
    }

    auto space_at_level = OtherBlocksHaveSpace(block_id);
    if (space_at_level) {
      this->RebalanceInterval(block_id, space_at_level);
      this->Insert(value, block_id);
      return;
    }

    this->IncreaseSize();
    this->Insert(value);
  }

  std::string ToString() {
    std::string result = "";
    for (auto element : content_) {
      result += element == 0 ? " " : std::to_string(element);
      result += ",";
    }
    result.erase(result.size() - 1);
    return result;
  }
};
}  // namespace array