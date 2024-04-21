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
    bool IsLeaf() { return pointers_.empty(); }

    bool DoOverflow() { return values_.size() >= order_; }

    void Split() {
      size_t middle_element = order_ / 2;
      ContentType middle = values_.at(middle_element);
      std::vector<ContentType> first_half, second_half;

      for (size_t i = 0; i < middle_element; i++)
        first_half.push_back(values_.at(i));

      for (size_t i = middle_element + 1; i < values_.size(); i++)
        second_half.push_back(values_.at(i));

      pointers_.push_back(std::make_shared<Node>(order_, first_half, this));
      pointers_.push_back(std::make_shared<Node>(order_, second_half, this));

      values_.clear();
      values_.push_back(middle);
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

    Node(OrderType order) : order_(order), parent_(this){};
    Node(OrderType order, std::vector<ContentType> values, Node* parent)
        : order_(order), parent_{parent}, values_(values){};

    std::string ValuesToString(const std::vector<ContentType>& values) {
      if (values.empty())
        return "";
      std::ostringstream oss;
      for (const auto& value : values) {
        oss << value << ", ";
      }

      std::string result = oss.str();
      result = result.substr(0, result.length() - 2);

      return result;
    }

    std::string ToString() {
      auto middle_point = pointers_.size() / 2;
      std::string result = "";
      if (!IsLeaf()) {
        for (size_t i = middle_point; i > 0; i--) {
          result += pointers_.at(i - 1)->ToString();
        }
      }

      auto values_string = ValuesToString(values_);
      std::ostringstream oss;
      oss << "[Values: (" << ValuesToString(values_) << ")]";
      result += oss.str();

      if (!IsLeaf()) {
        for (size_t i = pointers_.size(); i > middle_point; i--) {
          result += pointers_.at(i - 1)->ToString();
        }
      }
      return result;
    }
  };

  OrderType order_;
  std::shared_ptr<Node> head_;

 public:
  BTree(OrderType order)
      : order_(order), head_(std::make_shared<Node>(order_)) {}

  bool IsEmpty() { return head_->IsEmpty(); }

  OrderType GetOrder() { return order_; }

  void Insert(ContentType value) { head_->Insert(value); }

  std::string ToString() { return head_->ToString(); }
};

}  // namespace tree