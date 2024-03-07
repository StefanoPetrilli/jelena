#pragma once

namespace disjoint_set {

template <typename T,
          typename = typename std::enable_if<std::is_unsigned<T>::value>::type>
class DisjointSet {
 private:
 public:
  virtual T Find(T element) = 0;
  // virtual void Merge(T element) = 0;
  // virtual void Union(T first_element, T second_element) = 0;
  // virtual T GetSize() = 0;
};

}  // namespace disjoint_set