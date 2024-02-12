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
  T GetValue() { return this->value; }
};

template <typename T>
class LinkedList {
 private:
  std::shared_ptr<Node<T>> first_node_;
  std::shared_ptr<Node<T>> last_node_;
  size_t size_ = 0;

  std::string NodesToString() {
    auto result = std::string();
    auto current_node = first_node_;
    while (current_node) {
      result += current_node->ToString() + " ";
      current_node = current_node->Next();
    }
    result.pop_back();
    return result;
  }

  T GetNode(int index) {
    int current = 0;
    auto current_node = first_node_;

    while (current != index) {
      current_node = current_node->Next();
      current++;
    }

    return current_node->GetValue();
  }

  void InsertFirstNode(T value) {
    last_node_ = std::make_shared<Node<T>>(value);
    first_node_ = last_node_;
  }

  void InsertNode(T value) {
    auto new_node = std::make_shared<Node<T>>(value);
    last_node_->SetNext(new_node);
    new_node->SetPrevious(last_node_);
    last_node_ = new_node;
  }

  bool IsOutOfRange(size_t index) {
    return this->IsEmpty() || this->Size() <= index;
  }

 public:
  void Clear() {}

  bool IsEmpty() { return first_node_ == nullptr; }

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
               ? throw std::out_of_range(
                     "The linked list is smaller than the index searched")
               : GetNode(index);
  }
};
}  // namespace linked_list