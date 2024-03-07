#pragma once

#include <numeric>
#include "disjoint_set.h"

namespace disjoint_set {

template <typename T,
          typename = typename std::enable_if<std::is_unsigned<T>::value>::type>
class QuickUnion : public DisjointSet<T> {
 private:
  std::vector<T>
      blocks;  // TODO: is there a way of moving this field to the base class?

 public:
  QuickUnion(T size) : blocks(size) {
    std::iota(blocks.begin(), blocks.end(), 0);
  };
  T Find(T element) override { return element; }
  // void Merge(T element) override {}
  // void Union(T first_element, T second_element) override{};
  // T GetSize() override { return 0; };
};

}  // namespace disjoint_set