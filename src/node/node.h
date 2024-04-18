#pragma once

#include <memory>
#include <sstream>
#include <string>

//FIXME: this folder should not exist. As every data strcutre has his own
//       variation of a node it's too difficult to have a generalized version
//       and use inheritance.
//       This should be removed completely. Every DS should implement his own
//       version of this class.

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