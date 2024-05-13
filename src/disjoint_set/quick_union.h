#pragma once

#include <numeric>
#include "disjoint_set.h"

namespace disjoint_set {

template <typename T,
          typename = typename std::enable_if<std::is_unsigned<T>::value>::type>
class QuickUnion : public DisjointSet<T> {
 protected:
  bool IsNotRoot(T element) override {
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

#ifdef DISJOINT_SET_BENCHMARK
    this->ResetTotalPathLength();
#endif
  };
};

template <typename T,
          typename = typename std::enable_if<std::is_unsigned<T>::value>::type>
class QuickUnionFullCompression : public QuickUnion<T> {
 public:
  QuickUnionFullCompression(T size) : QuickUnion<T>(size) {}

  T FindBlock(T element) override {
    return this->FindBlockFullCompression(element);
  }

#ifdef DISJOINT_SET_BENCHMARK
  T GetTotalPointersUpdates() override {
    return this->GetFullCompressionTotalPointersUpdates();
  }
#endif
};

template <typename T,
          typename = typename std::enable_if<std::is_unsigned<T>::value>::type>
class QuickUnionPathSplitting : public QuickUnion<T> {
 public:
  QuickUnionPathSplitting(T size) : QuickUnion<T>(size) {}

  T FindBlock(T element) override {
    return this->FindBlockPathSplitting(element);
  }

#ifdef DISJOINT_SET_BENCHMARK
  T GetTotalPointersUpdates() override {
    return this->GetPathSplittingTotalPointersUpdates();
  }
#endif
};

template <typename T,
          typename = typename std::enable_if<std::is_unsigned<T>::value>::type>
class QuickUnionPathHalving : public QuickUnion<T> {
 public:
  QuickUnionPathHalving(T size) : QuickUnion<T>(size) {}

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