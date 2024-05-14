#pragma once

#include <algorithm>

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

  //TODO(StefanoPetrilli) rewrite using bit_width
  int Log2(int n) {
    int lg2 = 0;
    while (n > 1) {
      n /= 2;
      ++lg2;
    }
    return lg2;
  }

  double GetUpperTreshold(uint32_t level) {
    return 1.0 - ((1.0 - 0.5) * level) / (double)Log2(this->capacity_);
  }

  void UpdateVars(int capacity) {
    this->capacity_ = capacity;
    this->block_size_ = 1 << Log2(Log2(capacity) * 2);
    this->block_count_ = this->capacity_ / this->block_size_;
    this->level_count_ = Log2(this->block_count_);
  }

  ContentType GetMinimumFromBlock(uint32_t block_number) {
    auto starting_point = block_number * block_size_;
    auto result = std::find_if(content_.begin() + starting_point,
                               content_.begin() + starting_point + block_size_,
                               [](int value) { return value != 0; });

    return *result;
  }

  ContentType GetMaximumFromBlock(uint32_t block_number) {
    auto starting_point = block_number * block_size_;
    auto result = std::ranges::max_element(
        content_.begin() + starting_point,
        content_.begin() + starting_point + block_size_);

    return *result;
  }

  uint32_t FindBlock(ContentType value, uint32_t left_block,
                     uint32_t right_block) {
    if (left_block == right_block)
      return left_block;

    throw std::logic_error("Not implemented");
    return 1;
  }

  uint32_t FindBlock(ContentType value) {
    if (elements_count_ == 0)
      return 0;

    uint32_t middle_block = (this->block_count_ - 1) / 2;

    if (middle_block == this->block_count_ - 1) return 0;

    ContentType highest_middle = GetMaximumFromBlock(middle_block),
                lowest_left = GetMinimumFromBlock(0);

    if (value > lowest_left && value < highest_middle)
      return FindBlock(value, 0, middle_block);

    return FindBlock(value, middle_block + 1, this->block_count_ - 1);
  }

  void Insert(ContentType value, uint32_t block_number) {
    std::vector<ContentType> auxiliary_vector;
    auxiliary_vector.reserve(this->block_size_);
    auto initial_position = block_number * this->block_size_;

    for (auto i = initial_position; i < initial_position + this->block_size_;
         ++i) {
      if (this->content_.at(i) != 0)
        auxiliary_vector.push_back(content_.at(i));
    }
    auto position = std::ranges::lower_bound(auxiliary_vector, value);
    auxiliary_vector.insert(position, value);

    for (uint32_t i = 0; i < auxiliary_vector.size(); ++i) {
      this->content_[initial_position + i] = auxiliary_vector[i];
    }
    ++this->elements_count_;
  }

  uint32_t GetElementsInBlock(uint32_t block_number) {
    auto block_start =
        std::next(this->content_.begin(), block_number * this->block_size_);
    auto block_end = std::next(block_start, this->block_size_);

    return std::ranges::count_if(block_start, block_end,
                                 [](auto value) { return value != 0; });
  }

  bool BlockHasSpace(uint32_t block_number) {
    uint32_t elements_in_block = GetElementsInBlock(block_number);
    return elements_in_block < this->block_size_;
  }

  bool OtherBlocksHaveSpace(uint32_t block_number, uint32_t level) {
    if (level > this->level_count_)
      return false;

    auto upper_threshold = GetUpperTreshold(level);
    uint32_t search_window = level * this->block_size_;

    auto block_start =
        std::next(this->content_.begin(), block_number * this->block_size_);
    auto block_end = std::next(block_start, search_window);

    auto element_count = std::ranges::count_if(
        block_start, block_end, [](auto value) { return value != 0; });

    auto density = (element_count + 1) / search_window;
    if (density < upper_threshold)
      return true;
    OtherBlocksHaveSpace(block_number, level + 1);
  }

  void IncreaseSize() {
    auto new_capacity = this->capacity_ * 2;
    std::vector<ContentType> temp_content(new_capacity);
    double density = new_capacity / this->elements_count_;

    uint32_t control = 0;
    for (uint32_t i = 0; i < this->content_.size(); ++i) {
      if (this->content_.at(0)) {
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
    auto block_number = FindBlock(value);

    if (BlockHasSpace(block_number)) {
      Insert(value, block_number);
      return;
    }

    if (OtherBlocksHaveSpace(block_number, 2)) {
      throw std::logic_error("Not implemented");
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