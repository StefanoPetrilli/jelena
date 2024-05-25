#pragma once

#include <algorithm>
#include <bit>
#include <cmath>
#include <tuple>

namespace array {

static const uint8_t kInitialCapacity = 2;

template <typename ContentType, typename uint = uint32_t>
class PackedMemoryArray {
 private:
  std::vector<ContentType> content_;
  uint capacity_;
  ContentType elements_count_;
  uint block_size_;
  uint block_count_;
  uint level_count_;

  uint IntegerPartOfLog2(uint n) { return std::bit_width(n) - 1; }

  /*
  * A block_id on the current level corresponds to a different block_id
  * in a different level. Given the block_id and the level_difference, this
  * function finds the block_id and the size of the block on the upper
  * level.
  */
  std::tuple<uint, uint> GetNormalizedBlockAndSize(uint block_id,
                                                   uint level_difference) {
    return std::make_tuple(block_id / (1 << (level_difference - 1)),
                           block_size_ << (level_difference - 1));
  }

  double GetUpperTreshold(uint level) {
    return 1.0 - ((1.0 - 0.5) * level) /
                     static_cast<float>(IntegerPartOfLog2(capacity_));
  }

  void UpdateVariables(int capacity) {
    this->capacity_ = capacity;
    block_size_ = 1 << IntegerPartOfLog2(IntegerPartOfLog2(capacity) * 2);
    block_count_ = this->capacity_ / block_size_;
    level_count_ = IntegerPartOfLog2(block_count_);
  }

  ContentType GetMinimumFromBlock(uint block_id) {
    auto starting_point = block_id * block_size_;
    auto result = std::find_if(content_.begin() + starting_point,
                               content_.begin() + starting_point + block_size_,
                               [](int value) { return value != 0; });

    return *result;
  }

  ContentType GetMaximumFromBlock(uint block_id) {
    auto starting_point = block_id * block_size_;
    auto result = std::ranges::max_element(
        content_.begin() + starting_point,
        content_.begin() + starting_point + block_size_);

    return *result;
  }

  std::vector<ContentType> GetValuesInInterval(uint begin, uint offset) {
    std::vector<ContentType> result;
    std::ranges::copy_if(content_.begin() + begin,
                         content_.begin() + begin + offset,
                         std::back_inserter(result),
                         [](const auto& value) { return value != 0; });
    return result;
  }

  uint GetValuesCountInInterval(uint begin, uint offset) {
    return GetValuesInInterval(begin, offset).size();
  }

  void InsertPadding(std::vector<ContentType>& vector, uint target_size) {
    auto insertions = target_size - vector.size();
    if (!insertions)
      return;

    uint interval = std::ceil(vector.size() / static_cast<float>(insertions));

    for (uint i = 0; i < insertions; i++) {
      vector.insert(vector.begin() + std::min(i * interval + i,
                                              static_cast<uint>(vector.size())),
                    0);
    }
  }

  uint FindBlock(ContentType value, uint left_block, uint right_block) {
    if (left_block == right_block)
      return left_block;

    uint middle_block = left_block + ((right_block - left_block) / 2);
    ContentType highest_middle = GetMaximumFromBlock(middle_block);

    if (value < highest_middle)
      return FindBlock(value, 0, middle_block);

    return FindBlock(value, middle_block + 1, right_block);
  }

  uint FindBlock(ContentType value) {
    if (elements_count_ == 0)
      return 0;

    uint middle_block = (block_count_ - 1) / 2;

    if (middle_block == block_count_ - 1)
      return 0;

    ContentType highest_middle = GetMaximumFromBlock(middle_block);

    if (value < highest_middle)
      return FindBlock(value, 0, middle_block);

    return FindBlock(value, middle_block + 1, block_count_ - 1);
  }

  void Insert(ContentType value, uint block_id) {
    auto initial_position = block_id * block_size_;

    std::vector<ContentType> auxiliary_vector;
    auxiliary_vector.reserve(block_size_);
    auxiliary_vector = GetValuesInInterval(initial_position, block_size_);

    auto position = std::ranges::lower_bound(auxiliary_vector, value);
    auxiliary_vector.insert(position, value);

    InsertPadding(auxiliary_vector, block_size_);

    std::copy(auxiliary_vector.begin(), auxiliary_vector.end(),
              content_.begin() + initial_position);
    ++elements_count_;
  }

  void RebalanceInterval(uint block_id, uint level) {
    uint normalized_block_id, normalized_block_size;
    std::tie(normalized_block_id, normalized_block_size) =
        GetNormalizedBlockAndSize(block_id, level);

    auto initial_position = normalized_block_id * normalized_block_size;

    std::vector<ContentType> auxiliary_vector;
    auxiliary_vector.reserve(normalized_block_size);
    auxiliary_vector =
        GetValuesInInterval(initial_position, normalized_block_size);

    InsertPadding(auxiliary_vector, normalized_block_size);

    std::copy(auxiliary_vector.begin(), auxiliary_vector.end(),
              content_.begin() + initial_position);
  }

  uint GetElementsInBlock(uint block_id) {
    auto block_start = std::next(content_.begin(), block_id * block_size_);
    auto block_end = std::next(block_start, block_size_);

    return std::ranges::count_if(block_start, block_end,
                                 [](auto value) { return value != 0; });
  }

  bool BlockHasSpace(uint block_id) {
    uint elements_in_block = GetElementsInBlock(block_id);
    return elements_in_block < block_size_;
  }

  uint OtherBlocksHaveSpace(uint block_id, uint level = 1) {
    if (level > level_count_ + 1)
      return 0;

    auto upper_threshold = GetUpperTreshold(level);
    uint normalized_block_id, normalized_block_size;
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
    auto new_capacity = capacity_ * 2;
    std::vector<ContentType> temp_content(new_capacity);
    auto density = new_capacity / static_cast<float>(elements_count_);

    uint control = 0;
    for (uint i = 0; i < content_.size(); ++i) {
      if (content_.at(i)) {
        int idx = density * (control++);
        temp_content.at(idx) = content_.at(i);
      }
    }

    content_.swap(temp_content);
    UpdateVariables(new_capacity);
  }

 public:
  PackedMemoryArray() : capacity_(kInitialCapacity), elements_count_(0) {
    content_.resize(capacity_);
    UpdateVariables(capacity_);
  }

  void Insert(ContentType value) {
    auto block_id = FindBlock(value);

    if (BlockHasSpace(block_id)) {
      Insert(value, block_id);
      return;
    }

    auto space_at_level = OtherBlocksHaveSpace(block_id);
    if (space_at_level) {
      RebalanceInterval(block_id, space_at_level);
      Insert(value, block_id);
      return;
    }

    IncreaseSize();
    Insert(value);
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