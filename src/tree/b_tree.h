#pragma once

#include <algorithm>
#include <memory>

namespace tree {

template <typename ContentType, typename OrderType = uint16_t>
class BTree {

 private:
  class Node {
   private:
    OrderType order_;
    Node* parent_;
    std::vector<std::shared_ptr<Node>> pointers_;
    std::vector<ContentType> keys_;

   public:
#ifdef BTREE_BENCHMARK
    static uint32_t split_counter_;
#endif

    Node(OrderType order) : order_(order), parent_(this) {};
    Node(OrderType order, Node* parent) : order_(order), parent_(parent) {};
    Node(OrderType order, std::vector<ContentType> keys, Node* parent)
        : order_(order), parent_{parent}, keys_(keys) {};

    bool IsLeaf() const { return pointers_.empty(); }

    bool IsRoot() const { return this == parent_; }

    bool DoOverflow() const { return keys_.size() >= order_; }

    uint16_t Size() const { return keys_.size(); }

    std::vector<std::shared_ptr<Node>> GetPointers() const { return pointers_; }

    bool IsEmpty() const { return keys_.empty(); }

    void UpdateParent(Node* new_parent) { parent_ = new_parent; }

    void InsertKey(ContentType key) { keys_.push_back(key); }

    void Clear() {
      keys_.clear();
      pointers_.clear();
    }

    bool Contains(ContentType key) {
      if (IsLeaf())
        return std::find(keys_.begin(), keys_.end(), key) != keys_.end();

      auto it = std::lower_bound(keys_.begin(), keys_.end(), key);
      if (*it == key) return true;
      uint16_t i = std::distance(keys_.begin(), it);
      return pointers_.at(i)->Contains(key);
    }

    uint16_t FindInsertionLocation(ContentType key) {
      auto it = std::lower_bound(keys_.begin(), keys_.end(), key);
      return std::distance(keys_.begin(), it);
    }

    void InsertKey(ContentType key, uint16_t position) {
      keys_.insert(keys_.begin() + position, key);
    }

    void InsertPointers(std::shared_ptr<Node> first_half,
                        std::shared_ptr<Node> second_half, uint16_t location) {
      if (pointers_.size() > location)
        pointers_[location] = second_half;
      else
        pointers_.push_back(second_half);
      pointers_.insert(pointers_.begin() + location, first_half);
    }

    void InsertPointer(std::shared_ptr<Node> pointer) {
      pointers_.push_back(pointer);
    }

    void PopulateLeafSplitNode(std::shared_ptr<Node>& node, uint32_t start,
                               uint32_t end) {
      for (uint32_t i = start; i < end; i++)
        node->InsertKey(keys_.at(i));
    }

    void PopulateNonLeafSplitNode(std::shared_ptr<Node>& node, uint32_t start,
                                  uint32_t end, uint32_t additional_pointer) {
      for (uint32_t i = start; i < end; i++) {
        node->InsertKey(keys_.at(i));
        node->InsertPointer(pointers_.at(i));
      }
      node->InsertPointer(pointers_.at(additional_pointer));
    }

    void UpdateParentPointers(std::shared_ptr<Node> left_node,
                              std::shared_ptr<Node> right_node) {
      for (auto pointer : left_node->GetPointers())
        pointer->UpdateParent(left_node.get());

      for (auto pointer : right_node->GetPointers())
        pointer->UpdateParent(right_node.get());
    }

    void Split() {
#ifdef BTREE_BENCHMARK
      split_counter_++;
#endif
      uint32_t middle_element = order_ / 2 - (order_ % 2 == 0);
      ContentType middle = keys_.at(middle_element);

      auto left_node = std::make_shared<Node>(order_, parent_),
           right_node = std::make_shared<Node>(order_, parent_);

      if (IsLeaf()) {
        PopulateLeafSplitNode(left_node, 0, middle_element);
        PopulateLeafSplitNode(right_node, middle_element + 1, keys_.size());
      } else {
        PopulateNonLeafSplitNode(left_node, 0, middle_element, middle_element);
        PopulateNonLeafSplitNode(right_node, middle_element + 1, keys_.size(),
                                 keys_.size());
      }

      if (IsRoot()) {
        Clear();
        InsertPointers(left_node, right_node, 0);
        UpdateParentPointers(left_node, right_node);
        InsertKey(middle, 0);
      } else {
        uint16_t insertion_location = parent_->FindInsertionLocation(middle);

        parent_->InsertKey(middle, insertion_location);
        parent_->InsertPointers(left_node, right_node, insertion_location);

        UpdateParentPointers(left_node, right_node);

        if (parent_->DoOverflow())
          parent_->Split();
      }
    }

    void Insert(ContentType key) {
      auto position = std::upper_bound(keys_.begin(), keys_.end(), key);
      keys_.insert(position, key);

      if (DoOverflow())
        Split();
    }

    std::string ValuesToString(const std::vector<ContentType>& keys) {
      if (keys.empty())
        return "";

      std::string result = "";
      for (const auto& key : keys)
        result += std::to_string(key) + ", ";

      return result.substr(0, result.length() - 2);
    }

    std::string ToString() {
      auto middle_point = pointers_.size() / 2;
      std::string result = "";
      if (!IsLeaf()) {
        for (uint32_t i = middle_point; i > 0; i--) {
          result += pointers_.at(i - 1)->ToString();
        }
      }

      result += "(" + ValuesToString(keys_) + ")";

      if (!IsLeaf()) {
        for (uint32_t i = middle_point; i < pointers_.size(); i++) {
          result += pointers_.at(i)->ToString();
        }
      }
      return result;
    }

    Node* FindLeafForKey(ContentType key) {
      if (IsLeaf())
        return this;

      auto it = std::lower_bound(keys_.begin(), keys_.end(), key);
      uint16_t i = std::distance(keys_.begin(), it);
      return pointers_.at(i)->FindLeafForKey(key);
    }

    uint16_t GetHeight(uint16_t current_height) {
      if (IsLeaf()) {
        return current_height;
      }

      return pointers_.back()->GetHeight(current_height + 1);
    }
  };

  OrderType order_;
  std::unique_ptr<Node> root_;

 public:
  BTree(OrderType order)
      : order_(order), root_(std::make_unique<Node>(order_)) {
#ifdef BTREE_BENCHMARK
    Node::split_counter_ = 0;
#endif
  }

  bool IsEmpty() const { return root_->IsEmpty(); }

  OrderType GetOrder() const { return order_; }

  std::string ToString() const { return root_->ToString(); }

  uint32_t Size() const { return Size(root_); }

  void Insert(ContentType key) {
    if (root_->IsLeaf()) {
      root_->Insert(key);
      return;
    }

    auto leaf = root_->FindLeafForKey(key);
    leaf->Insert(key);
  }

  bool Contains(ContentType key) { return root_->Contains(key); }

  template <typename smart_pointer>
  uint32_t Size(const smart_pointer& node) const {
    uint32_t count = node->Size();
    for (const auto& pointer : node->GetPointers()) {
      count += Size(pointer);
    }
    return count;
  }

  uint16_t GetHeight() { return root_->GetHeight(1); }

#ifdef BTREE_BENCHMARK
  uint32_t GetSplitCount() { return Node::split_counter_; }
#endif
};

#ifdef BTREE_BENCHMARK
template <typename ContentType, typename OrderType>
uint32_t BTree<ContentType, OrderType>::Node::split_counter_;
#endif
}  // namespace tree