#pragma once

#include <optional>

namespace disjoint_set {

template <typename T>
class DisjointSet {
 protected:
  std::vector<T> blocks_;
  T distinct_blocks_;
  T GetFather(T element) { return this->blocks_.at(element); };
  virtual bool IsNotRoot(T element) = 0;
  bool IsRoot(T element) { return !this->IsNotRoot(element); };

#ifdef DISJOINT_SET_BENCHMARK
  std::optional<T> total_path_length_;
#endif
  void ResetTotalPathLength() {
#ifdef DISJOINT_SET_BENCHMARK
    total_path_length_ = std::nullopt;
#endif
  };

  T FindBlockFullCompression(T element) {
    auto representative = DisjointSet<T>::FindBlock(element);

    T current_index = element, previous_index;

    while (this->IsNotRoot(current_index)) {
      previous_index = current_index;
      current_index = this->GetFather(current_index);
      this->blocks_.at(previous_index) = representative;
    }

    this->ResetTotalPathLength();
    return representative;
  }

  T FindBlockPathSplitting(T element) {
    T current_index = element, previous_index;

    while (this->IsNotRoot(current_index)) {
      previous_index = current_index;
      current_index = this->GetFather(current_index);
      if (this->IsRoot(current_index))
        break;

      this->blocks_.at(previous_index) = this->GetFather(current_index);
    }

    this->ResetTotalPathLength();
    return current_index;
  }

  T FindBlockPathHalving(T element) {
    T current_index = element, previous_index;
    bool is_even = true;

    while (IsNotRoot(current_index)) {
      previous_index = current_index;
      current_index = this->GetFather(current_index);
      if (this->IsRoot(current_index))
        break;

      if (is_even)
        this->blocks_.at(previous_index) = this->GetFather(current_index);

      is_even = !is_even;
    }

    this->ResetTotalPathLength();
    return current_index;
  }

 public:
  DisjointSet(T size) : blocks_(size, -1), distinct_blocks_(size) {}

  virtual void MergeBlocks(T first_block, T second_block) = 0;
  virtual void MergeBlocks(std::tuple<T, T> merge_pair) {
    this->MergeBlocks(std::get<0>(merge_pair), std::get<1>(merge_pair));
  }

  T GetDistinctBlocks() {
    return distinct_blocks_;
  };

  virtual T FindBlock(T element) {
    auto current_index = element;

    while (this->IsNotRoot(current_index))
      current_index = this->GetFather(current_index);

    return current_index;
  }

#ifdef DISJOINT_SET_BENCHMARK
  T FindBlockDepth(T element) {
    auto current_index = element;
    T depth = 0;

    while (this->IsNotRoot(current_index)) {
      current_index = this->GetFather(current_index);
      depth++;
    }

    return depth;
  }

  T GetTotalPathlength() {
    if (this->total_path_length_.has_value())
      return this->total_path_length_.value();

    this->total_path_length_ = 0;

    for (size_t i = 0; i < this->blocks_.size(); ++i)
      *this->total_path_length_ += this->FindBlockDepth(i);

    return this->total_path_length_.value();
  }

  T virtual GetTotalPointersUpdates() {
    return 0;
  }

  T GetFullCompressionTotalPointersUpdates() {
    return this->GetTotalPathlength() -
           (this->blocks_.size() - this->distinct_blocks_);
  }

  T GetPathSplittingTotalPointersUpdates() {
    return GetFullCompressionTotalPointersUpdates();
  }

  T GetPathHalvingPointersUpdates() {
    T path_halving_cost = 0;
    for (size_t i = 0; i < this->blocks_.size(); ++i)
      path_halving_cost += this->FindBlockDepth(i) / 2;

    return path_halving_cost;
  }
#endif
};

}  // namespace disjoint_set