#pragma once

#include <memory>
#include <sstream>
#include <string>

namespace node {
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

  ~Node() {
    previous_node = nullptr;
    next_node = nullptr;
  }

  std::string ToString() {
    //TODO(StefanoPetrilli): Fully understand this snippet
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
}  // namespace node