#pragma once

#include <numeric>
#include "disjoint_set.h"

namespace disjoint_set {

template <typename T,
          typename = typename std::enable_if<std::is_unsigned<T>::value>::type>
class QuickUnion : public DisjointSet<T> {
 private:
  T IsNotRoot(T element) { return this->blocks_.at(element) != element; };

 public:
  QuickUnion(T size) : DisjointSet<T>(size) {
    std::iota(this->blocks_.begin(), this->blocks_.end(), 0);
  };

  T FindBlock(T element) override {
    auto current_index = element;

    while (IsNotRoot(current_index))
      current_index = this->GetFather(current_index);

    return current_index;
  }

  T FindBlockFullCompression(T element) override {
    auto representative = FindBlock(element);

    T current_index = element, previous_index;

    while (IsNotRoot(current_index)) {
      previous_index = current_index;
      current_index = this->GetFather(current_index);
      this->blocks_.at(previous_index) = representative;
    }

    return representative;
  }

  T FindBlockPathSplitting(T element) override {
    T current_index = element, previous_index;

    while (IsNotRoot(current_index)) {
      previous_index = current_index;
      current_index = this->GetFather(current_index);
      this->blocks_.at(previous_index) = this->GetFather(current_index);
    }

    return current_index;
  }

  T FindBlockPathHalving(T element) override {
    T current_index = element, previous_index;
    bool is_even = true;

    while (IsNotRoot(current_index)) {
      previous_index = current_index;
      current_index = this->GetFather(current_index);
      if (is_even)
        this->blocks_.at(previous_index) = this->GetFather(current_index);

      is_even = !is_even;
    }

    return current_index;
  }

  void MergeBlocks(T first_block, T second_block) override {
    this->blocks_.at(second_block) = this->blocks_.at(first_block);
  };
};

}  // namespace disjoint_set