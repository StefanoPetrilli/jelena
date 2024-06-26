#pragma once

#include <algorithm>
#include <numeric>
#include "weight_union.h"

namespace disjoint_set {

template <typename T>
class RankUnion : public WeightUnion<T> {
 private:
  T GetRootRank(T root) { return this->blocks_.at(root) * -1; }
  void MergeRoots(T larger_root, T larger_root_rank, T smaller_root,
                  T smaller_root_rank) {
    this->blocks_.at(larger_root) +=
        (smaller_root_rank == larger_root_rank) * -1;
    this->blocks_.at(smaller_root) = larger_root;
  }

 public:
  RankUnion(T size) : WeightUnion<T>(size){};

  using DisjointSet<T>::MergeBlocks;

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

template <typename T>
class RankUnionFullCompression : public RankUnion<T> {
 public:
  RankUnionFullCompression(T size) : RankUnion<T>(size) {}

  T FindBlock(T element) override {
    return this->FindBlockFullCompression(element);
  }

#ifdef DISJOINT_SET_BENCHMARK
  T GetTotalPointersUpdates() override {
    return this->GetFullCompressionTotalPointersUpdates();
  }
#endif
};

template <typename T>
class RankUnionPathSplitting : public RankUnion<T> {
 public:
  RankUnionPathSplitting(T size) : RankUnion<T>(size) {}

  T FindBlock(T element) override {
    return this->FindBlockPathSplitting(element);
  }

#ifdef DISJOINT_SET_BENCHMARK
  T GetTotalPointersUpdates() override {
    return this->GetPathSplittingTotalPointersUpdates();
  }
#endif
};

template <typename T>
class RankUnionPathHalving : public RankUnion<T> {
 public:
  RankUnionPathHalving(T size) : RankUnion<T>(size) {}

  T FindBlock(T element) override {
    return this->FindBlockPathHalving(element);
  }

#ifdef DISJOINT_SET_BENCHMARK
  T GetTotalPointersUpdates() override {
    return this->GetPathHalvingPointersUpdates();
  }
#endif
};

}  // namespace disjoint_set