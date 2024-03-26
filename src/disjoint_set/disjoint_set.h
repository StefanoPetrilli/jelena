#pragma once

namespace disjoint_set {

template <typename T>
class DisjointSet {
 protected:
  std::vector<T> blocks_;
  T distinct_blocks_;
  T GetFather(T element) { return this->blocks_.at(element); };

 public:
  DisjointSet(T size) : blocks_(size, -1), distinct_blocks_(size)  {}

  virtual T FindBlock(T element) = 0;
  virtual T FindBlockFullCompression(T element) = 0;
  virtual T FindBlockPathSplitting(T element) = 0;
  virtual T FindBlockPathHalving(T element) = 0;
  virtual void MergeBlocks(T first_block, T second_block) = 0;
  T GetDistinctBlocks() { return distinct_blocks_; };
  #ifdef FULL_BENCHMARK
  virtual T GetTotalPathLenght() = 0;
  #endif
};

}  // namespace disjoint_set