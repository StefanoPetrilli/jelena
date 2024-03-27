#pragma once

#include <numeric>
#include "disjoint_set.h"

namespace disjoint_set {

template <typename T,
          typename = typename std::enable_if<std::is_unsigned<T>::value>::type>
class QuickUnion : public DisjointSet<T> {
 private:
  T IsNotRoot(T element) override {
    return this->blocks_.at(element) != element;
  };

 public:
  QuickUnion(T size) : DisjointSet<T>(size) {
    std::iota(this->blocks_.begin(), this->blocks_.end(), 0);
  };
  using DisjointSet<T>::MergeBlocks;

  void MergeBlocks(T first_block, T second_block) override {
    auto root_first_block = this->FindBlock(first_block),
         root_second_block = this->FindBlock(second_block);
    if (root_second_block == root_first_block)
      return;
    this->blocks_.at(root_first_block) = root_second_block;
    this->distinct_blocks_--;

#ifdef FULL_BENCHMARK
    this->root_child_number_.at(root_first_block) = 0;
    this->root_child_number_.at(root_second_block)++;
    this->ResetTotalPathLength();
#endif
  };

};

}  // namespace disjoint_set