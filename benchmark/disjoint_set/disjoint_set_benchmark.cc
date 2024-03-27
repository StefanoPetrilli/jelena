
#include "disjoint_set_benchmark.h"

namespace disjoint_set_benchmark {
std::ofstream DisjointSetBenchmark::quick_union_statistics_;
std::ofstream DisjointSetBenchmark::weight_quick_union_statistics_;
std::ofstream DisjointSetBenchmark::rank_quick_union_statistics_;

TEST_F(DisjointSetBenchmark, QuickUnion) {
  uint16_t previous_size = 0;
  size_t cycles = 0;
  auto current_size = quick_union_set_.GetDistinctBlocks();

  while (current_size > 1) {
    quick_union_set_.MergeBlocks(distinct_pairs.at(cycles));

    cycles++;
    current_size = quick_union_set_.GetDistinctBlocks();

    if (previous_size != current_size) {
      previous_size = current_size;
      WriteStatistics(
          quick_union_statistics_, cycles, quick_union_set_.GetDistinctBlocks(),
          quick_union_set_.GetTotalPathLenght(),
          quick_union_set_.GetFullCompressionTotalPointersUpdates());
    }
  }
}

TEST_F(DisjointSetBenchmark, WeightQuickUnion) {
  uint16_t previous_size = 0;
  size_t cycles = 0;
  auto current_size = weighted_disjoint_set_.GetDistinctBlocks();

  while (current_size > 1) {
    weighted_disjoint_set_.MergeBlocks(distinct_pairs.at(cycles));

    cycles++;
    current_size = weighted_disjoint_set_.GetDistinctBlocks();

    if (previous_size != current_size) {
      previous_size = current_size;
      WriteStatistics(
          weight_quick_union_statistics_, cycles,
          weighted_disjoint_set_.GetDistinctBlocks(),
          weighted_disjoint_set_.GetTotalPathLenght(),
          weighted_disjoint_set_.GetFullCompressionTotalPointersUpdates());
    }
  }
}

TEST_F(DisjointSetBenchmark, RankQuickUnion) {
  uint16_t previous_size = 0;
  size_t cycles = 0;
  auto current_size = rank_disjoint_set_.GetDistinctBlocks();

  while (current_size > 1) {
    rank_disjoint_set_.MergeBlocks(distinct_pairs.at(cycles));

    cycles++;
    current_size = rank_disjoint_set_.GetDistinctBlocks();

    if (previous_size != current_size) {
      previous_size = current_size;
      WriteStatistics(
          rank_quick_union_statistics_, cycles,
          rank_disjoint_set_.GetDistinctBlocks(),
          rank_disjoint_set_.GetTotalPathLenght(),
          rank_disjoint_set_.GetFullCompressionTotalPointersUpdates());
    }
  }
}
}  // namespace disjoint_set_benchmark