#pragma once

#include <memory>
#include <sstream>
#include <string>

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