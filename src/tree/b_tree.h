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
    Node(OrderType order, std::vector<ContentType> values, Node* parent)
        : order_(order), parent_{parent}, values_(values){};

    bool IsLeaf() { return pointers_.empty(); }

    bool IsRoot() { return this == parent_; }

    bool DoOverflow() { return values_.size() >= order_; }

    //TODO(StefanoPetrilli): transform this into a binary search
    uint16_t FindInsertionLocation(ContentType value) {
      uint16_t i;
      for (i = 0; i < values_.size(); i++) {
        if (value > values_.at(i))
          return i;
      }
      return 0;
    }

    void InsertValue(ContentType value, uint16_t position) {
      values_.insert(values_.begin() + position, value);
    }

    void InsertPointers(std::shared_ptr<Node> first_half,
                        std::shared_ptr<Node> second_half, uint16_t location) {
      pointers_[location] = second_half;
      pointers_.insert(pointers_.begin() + location, first_half);
    }

    void Split() {
      size_t middle_element = order_ / 2;
      ContentType middle = values_.at(middle_element);
      std::vector<ContentType> first_half, second_half;

      for (size_t i = 0; i < middle_element; i++)
        first_half.push_back(values_.at(i));

      for (size_t i = middle_element + 1; i < values_.size(); i++)
        second_half.push_back(values_.at(i));

      if (IsRoot()) {
        pointers_.push_back(std::make_shared<Node>(order_, first_half, this));
        pointers_.push_back(std::make_shared<Node>(order_, second_half, this));

        values_.clear();
        values_.push_back(middle);
      } else {
        uint16_t insertion_location = parent_->FindInsertionLocation(middle);

        parent_->InsertValue(middle, insertion_location);
        parent_->InsertPointers(
            std::make_shared<Node>(order_, first_half, this),
            std::make_shared<Node>(order_, second_half, this),
            insertion_location);

        //TODO(StefanoPetrilli): verify if it has to split?
      }
    }

    void Insert(ContentType value) {
      values_.push_back(value);
      // TODO(StefanoPetrilli): This is overpower. As we know the array to be
      // already sorted it would make more sense to just put the element to be
      // inserted in the right position
      std::sort(values_.begin(), values_.end());

      if (DoOverflow())
        Split();
    }

    bool IsEmpty() { return values_.empty(); }

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
        for (size_t i = middle_point; i > 0; i--) {
          result += pointers_.at(i - 1)->ToString();
        }
      }

      result += "[Values: (" + ValuesToString(values_) + ")]";

      if (!IsLeaf()) {
        for (size_t i = middle_point; i < pointers_.size(); i++) {
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

  bool IsEmpty() { return head_->IsEmpty(); }

  OrderType GetOrder() { return order_; }

  void Insert(ContentType value) {
    if (head_->IsLeaf()) {
      head_->Insert(value);
      return;
    }

    auto leaf = head_->FindLeafForValue(value);
    leaf->Insert(value);
  }

  std::string ToString() { return head_->ToString(); }
};

}  // namespace tree