#pragma once

#include <algorithm>
#include <bit>
#include <cmath>
#include <optional>
#include <tuple>

namespace tree {

static const uint8_t kInitialCapacity = 4;

template <typename ContentType, typename uint = uint32_t>
class COBTree {
 private:
  std::vector<ContentType> content_;
  std::vector<ContentType> tree_;
  std::vector<uint> map_;
  std::vector<bool> is_leaf_;
  uint capacity_;
  ContentType elements_count_;
  uint block_size_;
  uint block_count_;
  uint level_count_;
  std::optional<ContentType> min_value_;

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
                           this->block_size_ << (level_difference - 1));
  }

  double GetUpperTreshold(uint level) {
    return 1.0 - ((1.0 - 0.5) * level) /
                     static_cast<float>(IntegerPartOfLog2(this->capacity_));
  }

  void UpdateVariables(int capacity) {
    this->capacity_ = capacity;
    this->block_size_ = 1 << IntegerPartOfLog2(IntegerPartOfLog2(capacity) * 2);
    this->block_count_ = this->capacity_ / this->block_size_;
    this->level_count_ = IntegerPartOfLog2(this->block_count_);
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
    std::ranges::copy_if(this->content_.begin() + begin,
                         this->content_.begin() + begin + offset,
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

  std::vector<uint> FromBlockIdToTreePositions(uint block_id) {
    std::vector<uint> result;

    for (size_t i = 0; i < this->map_.size(); i++) {
      if (map_.at(i) == block_id) {
        result.push_back(i);
      }
    }

    return result;
  }

  /*
  * Using the memory packed array, returns an array with the nodes
  * that compone the corresponding binary search tree in breadth first order.
  */
  std::tuple<std::vector<ContentType>, std::vector<uint>> BuildBFTree() {
    std::vector<ContentType> result;
    std::vector<uint> block_map;
    result.resize((this->block_count_ * 2) - 1);
    block_map.resize((this->block_count_ * 2) - 1);

    std::vector<ContentType> block_min;
    for (uint i = 0; i < this->block_count_; i++)
      block_min.push_back(this->GetMinimumFromBlock(i));

    uint stride = block_min.size() / 2;
    uint index = 0;
    while (stride >= 1) {
      auto counter = stride;
      while (counter < block_min.size()) {
        result.at(index) = block_min.at(stride);
        block_map.at(index) = stride;
        index++;
        counter *= 2;
      }
      stride /= 2;
    }

    std::copy_backward(block_min.begin(), block_min.end(), result.end());
    for (size_t i = index, y = 0; i < block_map.size(); ++i, ++y)
      block_map.at(i) = y;

    return std::make_tuple(result, block_map);
  }

  void BuildVEBTree(const std::vector<ContentType>& input_array,
                    std::vector<ContentType>& veb_array, uint start_index,
                    uint end_index, uint veb_index = 0) {
    if (start_index >= end_index) {
      return;
    }

    uint number_of_nodes = end_index - start_index;
    if (number_of_nodes == 1) {
      veb_array[veb_index] = input_array[start_index];
      return;
    }

    uint sqrt_nodes = static_cast<int>(std::sqrt(number_of_nodes));
    uint top_tree_size = sqrt_nodes;
    if (sqrt_nodes * sqrt_nodes < number_of_nodes) {
      top_tree_size += 1;
    }

    // Place the top nodes
    for (uint i = 0; i < top_tree_size; ++i) {
      if (start_index + i < end_index) {
        veb_array[veb_index + i] = input_array[start_index + i];
      }
    }

    // Recursively place the subtrees
    for (uint i = 0; i < top_tree_size; ++i) {
      uint subtree_start_index = start_index + top_tree_size + i * sqrt_nodes;
      uint subtree_end_index =
          std::min(subtree_start_index + sqrt_nodes, end_index);
      BuildVEBTree(input_array, veb_array, subtree_start_index,
                   subtree_end_index,
                   veb_index + top_tree_size + i * sqrt_nodes);
    }
  }

  uint LowerBoundVEB(const std::vector<ContentType>& veb_array,
                     uint start_index, uint end_index, ContentType target,
                     int current_best_index) {
    if (start_index >= end_index) {
      return current_best_index;  // Return the best candidate index found
    }
    uint number_of_nodes = end_index - start_index;
    if (number_of_nodes == 1) {
      if (veb_array[start_index] <= target) {
        return start_index;
      } else {
        return current_best_index;
      }
    }

    uint sqrt_nodes = static_cast<int>(std::sqrt(number_of_nodes));
    uint top_tree_size = sqrt_nodes;
    if (sqrt_nodes * sqrt_nodes < number_of_nodes) {
      top_tree_size += 1;
    }

    // Search in the top nodes
    for (uint i = 0; i < top_tree_size; ++i) {
      if (start_index + i < end_index) {
        if (veb_array[start_index + i] <= target) {
          current_best_index = start_index + i;
        }
      }
    }

    // Recursively search in the subtrees
    for (uint i = 0; i < top_tree_size; ++i) {
      uint subtree_start_index = start_index + top_tree_size + i * sqrt_nodes;
      uint subtree_end_index =
          std::min(subtree_start_index + sqrt_nodes, end_index);
      int candidateIndex =
          LowerBoundVEB(veb_array, subtree_start_index, subtree_end_index,
                        target, current_best_index);
      if (candidateIndex != -1 && veb_array[candidateIndex] <= target) {
        current_best_index = candidateIndex;
      }
    }

    return current_best_index;
  }

  void RebuildSearchTree() {
    tree_.resize((this->block_count_ * 2) - 1);
    is_leaf_.resize((this->block_count_ * 2) - 1);
    std::fill(is_leaf_.begin(), is_leaf_.end(), false);

    std::vector<ContentType> bf_tree;
    std::tie(bf_tree, this->map_) = BuildBFTree();
    BuildVEBTree(bf_tree, tree_, 0, tree_.size());
  }

  void UpdateSearchTree(ContentType value, uint block_id) {
    auto positions = FromBlockIdToTreePositions(block_id);
    for (auto position : positions) {
      tree_.at(position) = value;
    }
  }

  uint FindBlock(ContentType value) {
    if (min_value_.has_value() && this->min_value_.value() > value)
      return 0;

    auto e = LowerBoundVEB(this->tree_, 0, this->tree_.size(), value, 0);
    return map_[e];
  }

  void Insert(ContentType value, uint block_id) {
    auto initial_position = block_id * this->block_size_;

    std::vector<ContentType> auxiliary_vector;
    auxiliary_vector.reserve(this->block_size_);
    auxiliary_vector = GetValuesInInterval(initial_position, this->block_size_);

    if (auxiliary_vector.size() == 0) {
      auxiliary_vector.push_back(value);
    } else if (auxiliary_vector.at(0) > value) {
      auxiliary_vector.insert(auxiliary_vector.begin(), value);
      UpdateSearchTree(value, block_id);
    } else if (auxiliary_vector.at(auxiliary_vector.size() - 1) < value) {
      auxiliary_vector.push_back(value);
    } else {
      auto position = std::ranges::lower_bound(auxiliary_vector, value);
      auxiliary_vector.insert(position, value);
    }

    InsertPadding(auxiliary_vector, this->block_size_);

    std::copy(auxiliary_vector.begin(), auxiliary_vector.end(),
              this->content_.begin() + initial_position);
    ++this->elements_count_;
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
              this->content_.begin() + initial_position);
  }

  uint GetElementsInBlock(uint block_id) {
    auto block_start =
        std::next(this->content_.begin(), block_id * this->block_size_);
    auto block_end = std::next(block_start, this->block_size_);

    return std::ranges::count_if(block_start, block_end,
                                 [](auto value) { return value != 0; });
  }

  bool BlockHasSpace(uint block_id) {
    uint elements_in_block = GetElementsInBlock(block_id);
    return elements_in_block < this->block_size_;
  }

  uint OtherBlocksHaveSpace(uint block_id, uint level = 1) {
    if (level > this->level_count_ + 1)
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
    auto new_capacity = this->capacity_ * 2;
    std::vector<ContentType> temp_content(new_capacity);
    auto density = new_capacity / static_cast<float>(this->elements_count_);

    uint control = 0;
    for (uint i = 0; i < this->content_.size(); ++i) {
      if (this->content_.at(i)) {
        int idx = density * (control++);
        temp_content.at(idx) = this->content_.at(i);
      }
    }

    this->content_.swap(temp_content);
    this->UpdateVariables(new_capacity);
    this->RebuildSearchTree();
  }

  void UpdateMinValue(ContentType value) {
    if (!this->min_value_.has_value())
      min_value_ = value;
    else
      min_value_ = std::min(min_value_.value(), value);
  }

  std::string ToStringData() {
    std::string result = "";
    for (auto element : content_) {
      result += element == 0 ? " " : std::to_string(element);
      result += ",";
    }
    result.erase(result.size() - 1);
    return result;
  }

  std::string ToStringTree() {
    std::string result = "";
    for (auto element : tree_) {
      result += element == 0 ? " " : std::to_string(element);
      result += ",";
    }
    result.erase(result.size() - 1);
    return result;
  }

 public:
  COBTree() : capacity_(kInitialCapacity), elements_count_(0) {
    tree_.push_back(0);
    is_leaf_.push_back(true);
    content_.resize(capacity_);
    this->UpdateVariables(capacity_);
    this->map_.resize(1);
  }

  void Insert(ContentType value) {
    auto block_id = FindBlock(value);

    if (BlockHasSpace(block_id)) {
      this->Insert(value, block_id);
      this->UpdateMinValue(value);
      return;
    }

    auto space_at_level = OtherBlocksHaveSpace(block_id);
    if (space_at_level) {
      this->RebalanceInterval(block_id, space_at_level);
      this->Insert(value, block_id);
      this->UpdateMinValue(value);
      return;
    }

    this->IncreaseSize();
    this->Insert(value);
  }

  std::string ToString() {
    return "Data: [" + this->ToStringData() + "]\nTree: [" +
           this->ToStringTree() + "]";
  }
};
}  // namespace tree