#pragma once

#include <numeric>
#include "disjoint_set.h"

namespace disjoint_set {

template <typename T>
class WeightQuickUnion : public DisjointSet<T> {
 private:
  T IsNotRoot(T element) override { return this->blocks_.at(element) >= 0; };
  T GetRootWeight(T root) { return this->blocks_.at(root) * -1; }

  void MergeRoots(T larger_root, T smaller_root, T smaller_root_weight) {
    this->blocks_.at(smaller_root) = larger_root;
    this->blocks_.at(larger_root) -= smaller_root_weight;

#ifdef FULL_BENCHMARK
    this->root_child_number_.at(larger_root) +=
        this->root_child_number_.at(smaller_root) + 1;
    this->root_child_number_.at(smaller_root) = 0;
#endif
  }

 public:
  WeightQuickUnion(T size) : DisjointSet<T>(size){};

  using DisjointSet<T>::MergeBlocks;

  void MergeBlocks(T first_block, T second_block) override {
    auto first_block_root = this->FindBlock(first_block),
         second_block_root = this->FindBlock(second_block);

    if (first_block_root == second_block_root)
      return;

    auto first_block_root_weight = GetRootWeight(first_block_root),
         second_block_root_weight = GetRootWeight(second_block_root);

    if (first_block_root_weight >= second_block_root_weight)
      MergeRoots(first_block_root, second_block_root, second_block_root_weight);
    else
      MergeRoots(second_block_root, first_block_root, first_block_root_weight);

    this->distinct_blocks_--;
    this->ResetTotalPathLength();
  };
};

}  // namespace disjoint_set