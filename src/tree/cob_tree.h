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
                           block_size_ << (level_difference - 1));
  }

  double GetUpperTreshold(uint level) {
    return 1.0 - ((1.0 - 0.5) * level) /
                     static_cast<float>(IntegerPartOfLog2(capacity_));
  }

  void UpdateVariables(int capacity) {
    capacity_ = capacity;
    block_size_ = 1 << IntegerPartOfLog2(IntegerPartOfLog2(capacity) * 2);
    block_count_ = capacity_ / block_size_;
    level_count_ = IntegerPartOfLog2(block_count_);
  }

  ContentType GetMinimumFromBlock(uint block_id) {
    auto starting_point = block_id * block_size_;
    auto result = std::find_if(content_.begin() + starting_point,
                               content_.begin() + starting_point + block_size_,
                               [](int value) { return value != 0; });

    return *result;
  }

  /*
  * As the values in the blocks are ordered, we only need to search for
  * the first non-zero value in the block
  */
  ContentType GetMaximumFromBlock(uint block_id) {
    auto starting_point = block_id * block_size_;
    auto ending_point = starting_point + block_size_;

    auto rbegin = std::make_reverse_iterator(content_.begin() + ending_point);
    auto rend = std::make_reverse_iterator(content_.begin() + starting_point);

    auto result = std::ranges::find_if(
        rbegin, rend, [](ContentType value) { return value != 0; });

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

  /*
  * Using the memory packed array, returns an array with the nodes
  * that compone the corresponding binary search tree in breadth first order.
  */
  std::tuple<std::vector<ContentType>, std::vector<uint>> BuildBFTree() {
    std::vector<ContentType> result;
    std::vector<uint> block_map;
    result.resize((block_count_ * 2) - 1);
    block_map.resize((block_count_ * 2) - 1);

    std::vector<ContentType> block_min;
    for (uint i = 0; i < block_count_; i++)
      block_min.push_back(GetMinimumFromBlock(i));

    uint stride = block_min.size() / 2;
    uint index = 0;
    while (stride >= 1) {
      auto counter = stride;
      while (counter < block_min.size()) {
        result.at(index) = block_min.at(counter);
        block_map.at(index) = counter;
        index++;
        counter += stride * 2;
      }
      stride /= 2;
    }

    std::copy_backward(block_min.begin(), block_min.end(), result.end());
    for (size_t i = index, y = 0; i < block_map.size(); ++i, ++y)
      block_map.at(i) = y;

    return std::make_tuple(result, block_map);
  }

  std::vector<ContentType> GetCurrentLevelNodes(
      const std::vector<ContentType>& input_array, uint tree_index,
      uint level) {
    uint number_of_nodes = 1 << level;
    std::vector<ContentType> new_vector(
        input_array.begin() + tree_index,
        input_array.begin() + tree_index + number_of_nodes);
    return new_vector;
  }

  std::vector<ContentType> GetCurrentLevelNodesMap(uint tree_index,
                                                   uint level) {
    uint number_of_nodes = 1 << level;
    std::vector<ContentType> new_vector(
        map_.begin() + tree_index, map_.begin() + tree_index + number_of_nodes);
    return new_vector;
  }

  void BuildVEBTree(const std::vector<ContentType>& input_array,
                    std::vector<uint> new_map = {}, uint tree_index = 0,
                    uint level = 0) {

    if (level == 0)
      new_map.resize(input_array.size());

    uint initial_level = level;
    uint levels_in_input = 0;
    uint nodes_count_in_input = input_array.size() - tree_index;
    if (nodes_count_in_input == 0) {
      map_.swap(new_map);
      return;
    }
    while (nodes_count_in_input > 0) {
      nodes_count_in_input -= 1 << initial_level;
      initial_level++;
      levels_in_input++;
    }

    uint upper_tree_height, lower_tree_height;
    if (levels_in_input <= 2) {
      lower_tree_height = 0;
      upper_tree_height = levels_in_input;
    } else {
      if (levels_in_input % 2 == 1) {
        upper_tree_height = 1;
        lower_tree_height = levels_in_input - upper_tree_height;
      } else {
        lower_tree_height = levels_in_input / 2;
        upper_tree_height = levels_in_input - lower_tree_height;
      }
    }

    if (upper_tree_height == 1) {
      auto nodes = GetCurrentLevelNodes(input_array, tree_index, level);
      tree_.at(tree_index) = nodes.at(0);
      new_map.at(tree_index) = map_.at(0);
      tree_index++;
    } else if (upper_tree_height == 2) {
      auto nodes = GetCurrentLevelNodes(input_array, tree_index, level);
      auto nodes_map = GetCurrentLevelNodesMap(tree_index, level);
      auto nodes_child = GetCurrentLevelNodes(
          input_array, tree_index + nodes.size(), level + 1);
      auto nodes_child_map =
          GetCurrentLevelNodesMap(tree_index + nodes.size(), level + 1);

      for (size_t i = 0; i < nodes.size(); ++i) {
        tree_.at(tree_index) = nodes.at(i);
        new_map.at(tree_index) = nodes_map.at(i);
        tree_index++;
        tree_.at(tree_index) = nodes_child.at(2 * i);
        new_map.at(tree_index) = nodes_child_map.at(2 * i);
        tree_index++;
        tree_.at(tree_index) = nodes_child.at(2 * i + 1);
        new_map.at(tree_index) = nodes_child_map.at(2 * i + 1);
        tree_index++;
      }
    }

    BuildVEBTree(input_array, new_map, tree_index, level + upper_tree_height);
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
    tree_.resize((block_count_ * 2) - 1);

    std::vector<ContentType> bf_tree;
    std::tie(bf_tree, map_) = BuildBFTree();
    BuildVEBTree(bf_tree);
  }

  std::vector<uint> FromBlockIdToTreePositions(uint block_id) {
    std::vector<uint> result;

    for (size_t i = 0; i < map_.size(); i++) {
      if (map_.at(i) == block_id) {
        result.push_back(i);
      }
    }

    return result;
  }

  void UpdateSearchTree(ContentType value, uint block_id) {
    auto positions = FromBlockIdToTreePositions(block_id);
    for (auto position : positions) {
      tree_.at(position) = value;
    }
  }

  bool IsSmallerThanMinimum(ContentType value) {
    return min_value_.has_value() && min_value_.value() > value;
  }

  uint FindBlock(ContentType value) {
    if (IsSmallerThanMinimum(value))
      return 0;

    auto block = LowerBoundVEB(tree_, 0, tree_.size(), value, 0);
    return map_[block];
  }

  void Insert(ContentType value, uint block_id) {
    auto initial_position = block_id * block_size_;

    auto auxiliary_vector = GetValuesInInterval(initial_position, block_size_);
    auto insert_pos = std::ranges::lower_bound(auxiliary_vector, value);

    /*
    * If the value is the new minimum of the block we have to replace the
    * previous value in the tree
    */
    if (insert_pos == auxiliary_vector.begin())
      UpdateSearchTree(value, block_id);

    auxiliary_vector.insert(insert_pos, value);

    InsertPadding(auxiliary_vector, block_size_);

    std::copy(auxiliary_vector.begin(), auxiliary_vector.end(),
              content_.begin() + initial_position);
    ++elements_count_;
  }

  void RebalanceInterval(uint block_id, uint level) {
    auto [normalized_block_id, normalized_block_size] =
        GetNormalizedBlockAndSize(block_id, level);
    auto initial_position = normalized_block_id * normalized_block_size;
    auto auxiliary_vector =
        GetValuesInInterval(initial_position, normalized_block_size);

    InsertPadding(auxiliary_vector, normalized_block_size);

    auto modified_blocks = normalized_block_size / block_size_;
    auto starting_modification_id = block_id;

    while (starting_modification_id + modified_blocks > block_count_) {
      starting_modification_id = block_count_ - modified_blocks;
    }

    std::vector<ContentType> before_modification(modified_blocks);
    for (uint i = 0; i < modified_blocks; ++i) {
      before_modification.at(i) =
          GetMinimumFromBlock(starting_modification_id + i);
    }

    std::copy(auxiliary_vector.begin(), auxiliary_vector.end(),
              content_.begin() + initial_position);

    for (uint i = 0; i < modified_blocks; ++i) {
      uint modified_block_id = starting_modification_id + i;
      auto new_min = GetMinimumFromBlock(modified_block_id);
      if (new_min != before_modification.at(i)) {
        UpdateSearchTree(new_min, modified_block_id);
      }
    }
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
    RebuildSearchTree();
  }

  void UpdateMinValue(ContentType value) {
    if (!min_value_.has_value())
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
    content_.resize(capacity_);
    UpdateVariables(capacity_);
    map_.resize(1);
  }

  void Insert(ContentType value) {
    auto block_id = FindBlock(value);

    if (BlockHasSpace(block_id)) {
      Insert(value, block_id);
      UpdateMinValue(value);
      return;
    }

    auto space_at_level = OtherBlocksHaveSpace(block_id);
    if (space_at_level) {
      RebalanceInterval(block_id, space_at_level);
      Insert(value, block_id);
      UpdateMinValue(value);
      return;
    }

    IncreaseSize();
    Insert(value);
  }

  std::string ToString() {
    return "Data: [" + ToStringData() + "]\nTree: [" + ToStringTree() + "]";
  }
};
}  // namespace tree