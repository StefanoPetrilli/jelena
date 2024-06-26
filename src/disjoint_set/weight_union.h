#pragma once

#include <numeric>
#include "disjoint_set.h"

namespace disjoint_set {

template <typename T>
class WeightUnion : public DisjointSet<T> {
 private:
  bool IsNotRoot(T element) override { return this->blocks_.at(element) >= 0; };
  T GetRootWeight(T root) { return this->blocks_.at(root) * -1; }

  void MergeRoots(T larger_root, T smaller_root, T smaller_root_weight) {
    this->blocks_.at(smaller_root) = larger_root;
    this->blocks_.at(larger_root) -= smaller_root_weight;
  }

 public:
  WeightUnion(T size) : DisjointSet<T>(size){};

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
template <typename T>
class WeightUnionFullCompression : public WeightUnion<T> {
 public:
  WeightUnionFullCompression(T size) : WeightUnion<T>(size) {}

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
class WeightUnionPathSplitting : public WeightUnion<T> {
 public:
  WeightUnionPathSplitting(T size) : WeightUnion<T>(size) {}

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
class WeightUnionPathHalving : public WeightUnion<T> {
 public:
  WeightUnionPathHalving(T size) : WeightUnion<T>(size) {}

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