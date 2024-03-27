#pragma once

#include <numeric>
#include "disjoint_set.h"

namespace disjoint_set {

template <typename T,
          typename = typename std::enable_if<std::is_unsigned<T>::value>::type>
class QuickUnion : public DisjointSet<T> {
 private:
  T IsNotRoot(T element) override { return this->blocks_.at(element) != element; };

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

#ifdef FULL_BENCHMARK
    this->ResetTotalPathLength();
#endif

    return representative;
  }

  T FindBlockPathSplitting(T element) override {
    T current_index = element, previous_index;

    while (IsNotRoot(current_index)) {
      previous_index = current_index;
      current_index = this->GetFather(current_index);
      this->blocks_.at(previous_index) = this->GetFather(current_index);
    }

#ifdef FULL_BENCHMARK
    this->ResetTotalPathLength();
#endif

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

#ifdef FULL_BENCHMARK
    this->ResetTotalPathLength();
#endif

    return current_index;
  }

  void MergeBlocks(T first_block, T second_block) override {
    auto root_first_block = this->FindBlock(first_block),
         root_second_block = this->FindBlock(second_block);
    if (root_second_block == root_first_block)
      return;
    this->blocks_.at(root_first_block) = root_second_block;
    this->distinct_blocks_--;

#ifdef FULL_BENCHMARK
    this->root_child_number_.at(root_first_block) = 0;
    this->root_child_number_.at(root_second_block) ++;
    this->ResetTotalPathLength();
#endif
  };
};

}  // namespace disjoint_set