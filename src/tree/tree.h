#pragma once

#include "node.h"

namespace tree {

template <typename T>
class Tree {
 protected:
  std::shared_ptr<node::Node<T>> head_ = nullptr;

 public:
  bool IsEmpty() { return head_ == nullptr; }
  virtual void Insert(T value) = 0;
  virtual bool Remove(T value) = 0;
  virtual std::shared_ptr<node::Node<T>> Search(T value) = 0;
};

}  // namespace tree