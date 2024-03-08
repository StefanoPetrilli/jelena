#pragma once

#include <algorithm>
#include <numeric>
#include "disjoint_set.h"

namespace disjoint_set {

template <typename T>
class RankQuickUnion : public DisjointSet<T> {
 private:
  T IsNotRoot(T element) { return this->blocks_.at(element) >= 0; };
  T GetFather(T element) { return this->blocks_.at(element); };
  T GetRootRank(T root) { return this->blocks_.at(root) * -1; }

 public:
  RankQuickUnion(T size) : DisjointSet<T>(size){};

  T FindBlock(T element) override {
    auto element_root = element;

    while (IsNotRoot(element_root))
      element_root = GetFather(element_root);

    return element_root;
  };

  void MergeBlocks(T first_block, T second_block) override {
    auto first_block_root = FindBlock(first_block),
         second_block_root = FindBlock(second_block),
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