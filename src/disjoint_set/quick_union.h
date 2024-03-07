#pragma once

#include <numeric>
#include "disjoint_set.h"

namespace disjoint_set {

template <typename T,
          typename = typename std::enable_if<std::is_unsigned<T>::value>::type>
class QuickUnion : public DisjointSet<T> {
 public:
  QuickUnion(T size) : DisjointSet<T>(size) {
    std::iota(this->blocks_.begin(), this->blocks_.end(), 0);
  };

  T FindBlock(T element) override {
    auto current_index = element;

    while (this->blocks_.at(current_index) != current_index)
      current_index = this->blocks_.at(current_index);

    return current_index;
  }

  void MergeBlocks(T first_block, T second_block) override {
    this->blocks_.at(second_block) = this->blocks_.at(first_block);
  };
};

}  // namespace disjoint_set