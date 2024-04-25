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
    std::vector<ContentType> values_;

   public:
    Node(OrderType order) : order_(order), parent_(this){};
    Node(OrderType order, Node* parent) : order_(order), parent_(parent){};
    Node(OrderType order, std::vector<ContentType> values, Node* parent)
        : order_(order), parent_{parent}, values_(values){};

    bool IsLeaf() const { return pointers_.empty(); }

    bool IsRoot() const { return this == parent_; }

    bool DoOverflow() const { return values_.size() >= order_; }

    uint16_t Size() const { return values_.size(); }

    std::vector<std::shared_ptr<Node>> GetPointers() const { return pointers_; }

    bool IsEmpty() const { return values_.empty(); }

    void UpdateParent(Node* new_parent) { parent_ = new_parent; }

    void InsertValue(ContentType value) { values_.push_back(value); }

    void Clear() {
      values_.clear();
      pointers_.clear();
    }

    uint16_t FindInsertionLocation(ContentType value) {
      auto it = std::lower_bound(values_.begin(), values_.end(), value);
      return std::distance(values_.begin(), it);
    }

    void InsertValue(ContentType value, uint16_t position) {
      values_.insert(values_.begin() + position, value);
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
        node->InsertValue(values_.at(i));
    }

    void PopulateNonLeafSplitNode(std::shared_ptr<Node>& node, uint32_t start,
                                  uint32_t end, uint32_t additional_pointer) {
      for (uint32_t i = start; i < end; i++) {
        node->InsertValue(values_.at(i));
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
      uint32_t middle_element = order_ / 2 - (order_ % 2 == 0);
      ContentType middle = values_.at(middle_element);

      auto left_node = std::make_shared<Node>(order_, parent_),
           right_node = std::make_shared<Node>(order_, parent_);

      if (IsLeaf()) {
        PopulateLeafSplitNode(left_node, 0, middle_element);
        PopulateLeafSplitNode(right_node, middle_element + 1, values_.size());
      } else {
        PopulateNonLeafSplitNode(left_node, 0, middle_element, middle_element);
        PopulateNonLeafSplitNode(right_node, middle_element + 1, values_.size(),
                                 values_.size());
      }

      if (IsRoot()) {
        Clear();
        InsertPointers(left_node, right_node, 0);
        UpdateParentPointers(left_node, right_node);
        InsertValue(middle, 0);
      } else {
        uint16_t insertion_location = parent_->FindInsertionLocation(middle);

        parent_->InsertValue(middle, insertion_location);
        parent_->InsertPointers(left_node, right_node, insertion_location);

        UpdateParentPointers(left_node, right_node);

        if (parent_->DoOverflow())
          parent_->Split();
      }
    }

    void Insert(ContentType value) {
      auto position = std::upper_bound(values_.begin(), values_.end(), value);
      values_.insert(position, value);

      if (DoOverflow())
        Split();
    }

    std::string ValuesToString(const std::vector<ContentType>& values) {
      if (values.empty())
        return "";

      std::string result = "";
      for (const auto& value : values)
        result += std::to_string(value) + ", ";

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

      result += "(" + ValuesToString(values_) + ")";

      if (!IsLeaf()) {
        for (uint32_t i = middle_point; i < pointers_.size(); i++) {
          result += pointers_.at(i)->ToString();
        }
      }
      return result;
    }

    Node* FindLeafForValue(ContentType value) {
      if (IsLeaf())
        return this;

      uint16_t i;
      for (i = 0; i < values_.size(); i++) {
        if (value > values_.at(i))
          continue;
        return pointers_.at(i)->FindLeafForValue(value);
      }

      return pointers_.back()->FindLeafForValue(value);
    }
  };

  OrderType order_;
  std::shared_ptr<Node> head_;

 public:
  BTree(OrderType order)
      : order_(order), head_(std::make_shared<Node>(order_)) {}

  bool IsEmpty() const { return head_->IsEmpty(); }

  OrderType GetOrder() const { return order_; }

  std::string ToString() const { return head_->ToString(); }

  uint32_t Size() const { return Size(head_); }

  void Insert(ContentType value) {
    if (head_->IsLeaf()) {
      head_->Insert(value);
      return;
    }

    auto leaf = head_->FindLeafForValue(value);
    leaf->Insert(value);
  }

  uint32_t Size(const std::shared_ptr<Node>& node) const {
    uint32_t count = node->Size();
    for (const auto& pointer : node->GetPointers()) {
      count += Size(pointer);
    }
    return count;
  }
};

}  // namespace tree