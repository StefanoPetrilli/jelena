#pragma once

#include <memory>

namespace tree {

template <typename T>
class BinaryTree {

 private:
  class Node {
   private:
    T value;
    std::shared_ptr<Node> previous_node;
    std::shared_ptr<Node> next_node;

   public:
    Node(T value, std::shared_ptr<Node> previous_node = nullptr,
         std::shared_ptr<Node> next_node = nullptr)
        : value(value), previous_node(previous_node), next_node(next_node) {}

    ~Node() {
      previous_node = nullptr;
      next_node = nullptr;
    }

    std::string ToString() {
      std::ostringstream oss;
      oss << value;
      return oss.str();
    }

    bool HasNext() { return this->next_node != nullptr; }
    bool HasPrevious() { return this->previous_node != nullptr; }

    void SetNext(std::shared_ptr<Node> node) { next_node = node; }
    void SetPrevious(std::shared_ptr<Node> node) { previous_node = node; }

    std::shared_ptr<Node> GetNextNode() { return next_node; }
    std::shared_ptr<Node> GetPreviousNode() { return previous_node; }

    T GetValue() { return this->value; }
  };

  std::shared_ptr<Node> head_ = nullptr;

 public:
  bool IsEmpty() { return this->head_ == nullptr; }

  void Insert(T value) {
    if (this->IsEmpty()) {
      head_ = std::make_shared<Node>(value);
    }

    if (head_->GetValue() < value && head_->GetNextNode() == nullptr) {
      head_->SetNext(std::make_shared<Node>(value));
    }
  }

  bool Remove(T value) {
    if (this->IsEmpty())
      return false;

    if (head_->GetValue() == value) {
      head_ = nullptr;
      return true;
    }

    return true;
  }

  std::shared_ptr<Node> Search(T value) {
    if (this->IsEmpty())
      return nullptr;

    if (this->head_->GetValue() == value) {
      return this->head_;
    }

    return nullptr;
  }
};

}  // namespace tree