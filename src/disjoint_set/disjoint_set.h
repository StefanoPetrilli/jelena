#pragma once

namespace disjoint_set {

template <typename T,
          typename = typename std::enable_if<std::is_unsigned<T>::value>::type>
class DisjointSet {
 protected:
  std::vector<T> blocks_;

 public:
  DisjointSet(T size) : blocks_(size) {}

  virtual T FindBlock(T element) = 0;
  virtual void MergeBlocks(T first_block, T second_block) = 0;
};

}  // namespace disjoint_set