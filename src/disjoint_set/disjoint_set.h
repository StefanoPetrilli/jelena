#pragma once

namespace disjoint_set {

template <typename T>
class DisjointSet {
 protected:
  std::vector<T> blocks_;

 public:
  DisjointSet(T size) : blocks_(size, -1) {}

  virtual T FindBlock(T element) = 0;
  virtual void MergeBlocks(T first_block, T second_block) = 0;
};

}  // namespace disjoint_set