#pragma once

namespace disjoint_set {

template <typename T>
class DisjointSet {
 protected:
  std::vector<T> blocks_;
  T GetFather(T element) { return this->blocks_.at(element); };

 public:
  DisjointSet(T size) : blocks_(size, -1) {}

  virtual T FindBlock(T element) = 0;
  virtual T FindBlockFullCompression(T element) = 0;
  virtual T FindBlockPathSplitting(T element) = 0;
  virtual T FindBlockPathHalving(T element) = 0;
  virtual void MergeBlocks(T first_block, T second_block) = 0;
};

}  // namespace disjoint_set