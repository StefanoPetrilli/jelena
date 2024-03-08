#pragma once

#include <numeric>
#include "disjoint_set.h"

namespace disjoint_set {

template <typename T>
class WeightedQuickUnion : public DisjointSet<T> {
 private:
  T IsNotRoot(T element) { return this->blocks_.at(element) >= 0; };
  T GetFather(T element) { return this->blocks_.at(element); };
  T GetRootWeight(T root) { return this->blocks_.at(root) * -1; }

 public:
  WeightedQuickUnion(T size) : DisjointSet<T>(size){};

  T FindBlock(T element) override {
    auto element_root = element;

    while (IsNotRoot(element_root))
      element_root = GetFather(element_root);

    return element_root;
  };

  void MergeBlocks(T first_block, T second_block) override {
    auto first_block_root = FindBlock(first_block),
         second_block_root = FindBlock(second_block),
         first_block_root_weight = GetRootWeight(first_block_root),
         second_block_root_weight = GetRootWeight(second_block_root);

    if (first_block_root_weight >= second_block_root_weight) {
      this->blocks_.at(second_block_root) = first_block_root;
      this->blocks_.at(first_block_root) -= second_block_root_weight;
    } else {
      this->blocks_.at(first_block_root) = second_block_root;
      this->blocks_.at(second_block_root) -= first_block_root_weight;
    }
  };
};

}  // namespace disjoint_set