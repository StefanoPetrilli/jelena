#pragma once

#include <algorithm>
#include <numeric>
#include "weight_quick_union.h"

namespace disjoint_set {

template <typename T>
class RankQuickUnion : public WeightQuickUnion<T> {
 private:
  T GetRootRank(T root) { return this->blocks_.at(root) * -1; }
  void MergeRoots(T larger_root, T larger_root_rank, T smaller_root,
                  T smaller_root_rank) {
    this->blocks_.at(larger_root) +=
        (smaller_root_rank == larger_root_rank) * -1;
    this->blocks_.at(smaller_root) = larger_root;

#ifdef FULL_BENCHMARK
    this->root_child_number_.at(larger_root) +=
        this->root_child_number_.at(smaller_root) + 1;
    this->root_child_number_.at(smaller_root) = 0;
#endif
  }

 public:
  RankQuickUnion(T size) : WeightQuickUnion<T>(size){};

  void MergeBlocks(T first_block, T second_block) override {
    auto first_block_root = this->FindBlock(first_block),
         second_block_root = this->FindBlock(second_block);

    if (first_block_root == second_block_root)
      return;

    auto first_block_root_rank = GetRootRank(first_block_root),
         second_block_root_rank = GetRootRank(second_block_root);

    if (first_block_root_rank >= second_block_root_rank)
      MergeRoots(first_block_root, first_block_root_rank, second_block_root,
                 second_block_root_rank);
    else
      MergeRoots(second_block_root, second_block_root_rank, first_block_root,
                 first_block_root_rank);
    this->distinct_blocks_--;
    this->ResetTotalPathLength();
  };
};

}  // namespace disjoint_set