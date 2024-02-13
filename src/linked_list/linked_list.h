#pragma once

#include <memory>
#include <sstream>
#include <string>

namespace linked_list {

template <typename T>
class Node {
 private:
  T value;
  std::shared_ptr<Node> previous_node;
  std::shared_ptr<Node> next_node;

 public:
  Node(T value, std::shared_ptr<Node> previous_node = nullptr,
       std::shared_ptr<Node> next_node = nullptr)
      : value(value), previous_node(previous_node), next_node(next_node) {}
  std::string ToString() {
    //TODO(StefanoPetrilli): Fully understand this snippet
    std::ostringstream oss;
    oss << value;
    return oss.str();
  }
  bool HasNext() { return this->next_node != nullptr; }
  std::shared_ptr<Node> Next() { return next_node; }
  void SetNext(std::shared_ptr<Node> node) { next_node = node; }
  void SetPrevious(std::shared_ptr<Node> node) { previous_node = node; }
  std::shared_ptr<Node> GetNextNode() { return next_node; }
  std::shared_ptr<Node> GetPreviousNode() { return previous_node; }
  T GetValue() { return this->value; }
};

template <typename T>
class LinkedList {
 private:
  std::shared_ptr<Node<T>> head_;
  std::shared_ptr<Node<T>> tail_;
  size_t size_ = 0;

  std::string NodesToString() {
    auto result = std::string();
    auto current_node = head_;
    while (current_node) {
      result += current_node->ToString() + " ";
      current_node = current_node->Next();
    }
    result.pop_back();
    return result;
  }

  std::shared_ptr<Node<T>> GetNode(size_t index) {
    size_t current = 0;
    auto current_node = head_;

    while (current != index) {
      current_node = current_node->Next();
      current++;
    }

    return current_node;
  }

  T GetNodeValue(size_t index) { return GetNode(index)->GetValue(); }

  void InsertFirstNode(T value) {
    tail_ = std::make_shared<Node<T>>(value);
    head_ = tail_;
  }

  void InsertNode(T value) {
    auto new_node = std::make_shared<Node<T>>(value);
    tail_->SetNext(new_node);
    new_node->SetPrevious(tail_);
    tail_ = new_node;
  }

  void DeleteNode(std::shared_ptr<Node<T>> node) {
    auto next_node = node->GetNextNode();
    auto previous_node = node->GetPreviousNode();

    previous_node->SetNext(next_node);
    next_node->SetPrevious(previous_node);
  }

  void DeleteHead() { head_->HasNext() ? ReplaceHead() : DeleteLastElement(); }

  void ReplaceHead() {
    head_ = head_->GetNextNode();
    head_->SetPrevious(nullptr);
  }

  void DeleteLastElement() {
    head_ = nullptr;
    tail_ = nullptr;
  }

  void DeleteTail() {
    tail_ = tail_->GetPreviousNode();
    tail_->SetNext(nullptr);
  }

  bool IsOutOfRange(size_t index) {
    return this->IsEmpty() || this->Size() <= index;
  }

 public:
  void Clear() {}

  bool IsEmpty() { return head_ == nullptr; }

  size_t Size() { return size_; }

  std::string ToString() {
    return this->IsEmpty() ? std::string() : NodesToString();
  }

  void Insert(T value) {
    this->IsEmpty() ? InsertFirstNode(value) : InsertNode(value);
    size_++;
  }

  T operator[](size_t index) {
    return IsOutOfRange(index)
               ? throw std::out_of_range("The index is out of range")
               : GetNodeValue(index);
  }

  void Delete(size_t index) {
    if (IsOutOfRange(index))
      throw std::out_of_range("The index is out of range");

    if (index == 0)
      DeleteHead();
    else if (index == this->Size() - 1)
      DeleteTail();
    else {
      auto node = GetNode(index);
      DeleteNode(node);
    }

    size_--;
  }
};
}  // namespace linked_list