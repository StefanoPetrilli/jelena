#pragma once

#include <algorithm>
#include <numeric>
#include "weight_quick_union.h"

namespace disjoint_set {

template <typename T>
class RankQuickUnion : public WeightQuickUnion<T> {
 private:
  T GetRootRank(T root) { return this->blocks_.at(root) * -1; }

 public:
  RankQuickUnion(T size) : WeightQuickUnion<T>(size){};

  void MergeBlocks(T first_block, T second_block) override {
    auto first_block_root = this->FindBlock(first_block),
         second_block_root = this->FindBlock(second_block),
         first_block_root_rank = GetRootRank(first_block_root),
         second_block_root_rank = GetRootRank(second_block_root);

    if (first_block_root_rank >= second_block_root_rank) {
      this->blocks_.at(first_block_root) -= second_block_root_rank;
      this->blocks_.at(first_block_root) +=
          std::min(second_block_root_rank, (T)(first_block_root_rank - 1));
      this->blocks_.at(second_block_root) = first_block_root;
    } else {
      this->blocks_.at(second_block_root) -= first_block_root_rank;
      this->blocks_.at(second_block_root) +=
          std::min(first_block_root_rank, (T)(second_block_root_rank - 1));
      this->blocks_.at(first_block_root) = second_block_root;
    }
  };
};

}  // namespace disjoint_set