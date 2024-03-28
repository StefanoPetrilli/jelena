
#include "disjoint_set_benchmark.h"

namespace disjoint_set_benchmark {
std::ofstream DisjointSetBenchmark::quick_union_statistics_;
std::ofstream DisjointSetBenchmark::weight_quick_union_statistics_;
std::ofstream DisjointSetBenchmark::rank_quick_union_statistics_;

TEST_F(DisjointSetBenchmark, QuickUnion) {
  uint16_t previous_size = 0, cycles = 0, cahnge_counter = 0,
           current_size = quick_union_set_.GetDistinctBlocks();

  while (current_size > 1) {
    quick_union_set_.MergeBlocks(distinct_pairs.at(cycles));

    cycles++;
    current_size = quick_union_set_.GetDistinctBlocks();

    if (previous_size != current_size) {
      previous_size = current_size;
      cahnge_counter++;
      if (cahnge_counter % kDelta_)
        continue;

      WriteStatistics(quick_union_statistics_,
                      quick_union_set_.GetDistinctBlocks(), cycles,
                      quick_union_set_.GetTotalPathLenght(),
                      quick_union_set_.GetFullCompressionTotalPointersUpdates(),
                      quick_union_set_.GetPathSplittingTotalPointersUpdates(),
                      quick_union_set_.GetPathHalvingPointersUpdates());
    }
  }
}

TEST_F(DisjointSetBenchmark, WeightQuickUnion) {
  uint16_t previous_size = 0, cycles = 0, cahnge_counter = 0,
           current_size = weighted_disjoint_set_.GetDistinctBlocks();

  while (current_size > 1) {
    weighted_disjoint_set_.MergeBlocks(distinct_pairs.at(cycles));

    cycles++;
    current_size = weighted_disjoint_set_.GetDistinctBlocks();

    if (previous_size != current_size) {
      previous_size = current_size;
      cahnge_counter++;
      if (cahnge_counter % kDelta_)
        continue;

      WriteStatistics(
          weight_quick_union_statistics_,
          weighted_disjoint_set_.GetDistinctBlocks(), cycles,
          weighted_disjoint_set_.GetTotalPathLenght(),
          weighted_disjoint_set_.GetFullCompressionTotalPointersUpdates(),
          weighted_disjoint_set_.GetPathSplittingTotalPointersUpdates(),
          weighted_disjoint_set_.GetPathHalvingPointersUpdates());
    }
  }
}

TEST_F(DisjointSetBenchmark, RankQuickUnion) {
  uint16_t previous_size = 0, cycles = 0, cahnge_counter = 0,
           current_size = rank_disjoint_set_.GetDistinctBlocks();

  while (current_size > 1) {
    rank_disjoint_set_.MergeBlocks(distinct_pairs.at(cycles));

    cycles++;
    current_size = rank_disjoint_set_.GetDistinctBlocks();

    if (previous_size != current_size) {
      previous_size = current_size;
      cahnge_counter++;
      if (cahnge_counter % kDelta_)
        continue;

      WriteStatistics(
          rank_quick_union_statistics_, rank_disjoint_set_.GetDistinctBlocks(),
          cycles, rank_disjoint_set_.GetTotalPathLenght(),
          rank_disjoint_set_.GetFullCompressionTotalPointersUpdates(),
          rank_disjoint_set_.GetPathSplittingTotalPointersUpdates(),
          rank_disjoint_set_.GetPathHalvingPointersUpdates());
    }
  }
}
}  // namespace disjoint_set_benchmark