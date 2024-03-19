#pragma once

#include <numeric>
#include "disjoint_set.h"

namespace disjoint_set {

template <typename T>
class WeightQuickUnion : public DisjointSet<T> {
 private:
  T IsNotRoot(T element) { return this->blocks_.at(element) >= 0; };
  T GetRootWeight(T root) { return this->blocks_.at(root) * -1; }

  void MergeRoots(T larger_root, T smaller_root, T smaller_root_weight) {
    this->blocks_.at(smaller_root) = larger_root;
    this->blocks_.at(larger_root) -= smaller_root_weight;
  }

 public:
  WeightQuickUnion(T size) : DisjointSet<T>(size){};

  T FindBlock(T element) override {
    auto current_index = element;

    while (IsNotRoot(current_index))
      current_index = this->GetFather(current_index);

    return current_index;
  };

  T FindBlockFullCompression(T element) override {
    auto representative = FindBlock(element);

    T current_index = element, previous_index;

    while (IsNotRoot(current_index)) {
      previous_index = current_index;
      current_index = this->GetFather(current_index);
      this->blocks_.at(previous_index) = representative;
    }

    return representative;
  }

  T FindBlockPathSplitting(T element) override {
    T current_index = element, previous_index;

    while (IsNotRoot(current_index)) {
      previous_index = current_index;
      current_index = this->GetFather(current_index);
      this->blocks_.at(previous_index) = this->GetFather(current_index);
    }

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

    return current_index;
  }

  void MergeBlocks(T first_block, T second_block) override {
    auto first_block_root = FindBlock(first_block),
         second_block_root = FindBlock(second_block),
         first_block_root_weight = GetRootWeight(first_block_root),
         second_block_root_weight = GetRootWeight(second_block_root);

    if (first_block_root_weight >= second_block_root_weight)
      MergeRoots(first_block_root, second_block_root, second_block_root_weight);
    else
      MergeRoots(second_block_root, first_block_root, first_block_root_weight);
  };
};

}  // namespace disjoint_set