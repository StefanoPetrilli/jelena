#pragma once

#include <memory>
#include "node.h"
#include "tree.h"

namespace tree {

template <typename T>
class BinaryTree : public Tree<T> {

 public:
  void Insert(T value) override {
    if (this->IsEmpty()) {
      this->head_ = std::make_shared<node::Node<T>>(value);
    }

    if (this->head_->GetValue() < value &&
        this->head_->GetNextNode() == nullptr) {
      this->head_->SetNext(std::make_shared<node::Node<T>>(value));
    }
  }

  virtual bool Remove(T value) override {
    if (this->IsEmpty())
      return false;

    if (this->head_->GetValue() == value) {
      this->head_ = nullptr;
      return true;
    }

    return true;
  }

  virtual std::shared_ptr<node::Node<T>> Search(T value) override {
    if (this->IsEmpty())
      return nullptr;

    if (this->head_->GetValue() == value) {
      return this->head_;
    }

    return nullptr;
  }
};

}  // namespace tree