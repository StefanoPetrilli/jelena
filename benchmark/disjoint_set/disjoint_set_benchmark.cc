
#include "disjoint_set_benchmark.h"

namespace disjoint_set_benchmark {
std::ofstream DisjointSetBenchmark::quick_union_statistics_;
std::ofstream DisjointSetBenchmark::weight_quick_union_statistics_;
std::ofstream DisjointSetBenchmark::rank_quick_union_statistics_;

TEST_F(DisjointSetBenchmark, QuickUnion) {
  std::vector<Statistics> statistics(kSize_ / kDelta_);
  disjoint_set::QuickUnion<uint16_t> quick_union_set(0);

  for (int i = 0; i < kNumberExecution_; ++i) {
    std::shuffle(distinct_pairs.begin(), distinct_pairs.end(), rng);
    quick_union_set = disjoint_set::QuickUnion<uint16_t>(kSize_);
    uint16_t previous_size = 0, cycles = 0, change_counter = 0,
             current_size = quick_union_set.GetDistinctBlocks();

    while (current_size > 1) {
      quick_union_set.MergeBlocks(distinct_pairs.at(cycles));

      cycles++;
      current_size = quick_union_set.GetDistinctBlocks();

      if (previous_size != current_size) {
        previous_size = current_size;
        change_counter++;
        if (change_counter % kDelta_)
          continue;

        statistics.at(change_counter / kDelta_)
            .update(cycles, quick_union_set.GetDistinctBlocks(),
                    quick_union_set.GetTotalPathLenght(),
                    quick_union_set.GetFullCompressionTotalPointersUpdates(),
                    quick_union_set.GetPathSplittingTotalPointersUpdates(),
                    quick_union_set.GetPathHalvingPointersUpdates());
      }
    }
  }

  for (auto element : statistics) {
    if (element.counter > kCutoff)
      WriteStatistics(quick_union_statistics_, element);
  }
}

TEST_F(DisjointSetBenchmark, WeightQuickUnion) {
  std::vector<Statistics> statistics(kSize_ / kDelta_);
  disjoint_set::WeightQuickUnion<int16_t> weighted_disjoint_set(0);

  for (int i = 0; i < kNumberExecution_; ++i) {
    std::shuffle(distinct_pairs.begin(), distinct_pairs.end(), rng);
    weighted_disjoint_set = disjoint_set::WeightQuickUnion<int16_t>(kSize_);
    uint16_t previous_size = 0, cycles = 0, change_counter = 0,
             current_size = weighted_disjoint_set.GetDistinctBlocks();

    while (current_size > 1) {
      weighted_disjoint_set.MergeBlocks(distinct_pairs.at(cycles));

      cycles++;
      current_size = weighted_disjoint_set.GetDistinctBlocks();

      if (previous_size != current_size) {
        previous_size = current_size;
        change_counter++;
        if (change_counter % kDelta_)
          continue;

        statistics.at(change_counter / kDelta_)
            .update(
                cycles, weighted_disjoint_set.GetDistinctBlocks(),
                weighted_disjoint_set.GetTotalPathLenght(),
                weighted_disjoint_set.GetFullCompressionTotalPointersUpdates(),
                weighted_disjoint_set.GetPathSplittingTotalPointersUpdates(),
                weighted_disjoint_set.GetPathHalvingPointersUpdates());
      }
    }
  }

  for (auto element : statistics) {
    if (element.counter > kCutoff)
      WriteStatistics(weight_quick_union_statistics_, element);
  }
}

TEST_F(DisjointSetBenchmark, RankQuickUnion) {
  std::vector<Statistics> statistics(kSize_ / kDelta_);
  disjoint_set::RankQuickUnion<int16_t> rank_disjoint_set(0);

  for (int i = 0; i < kNumberExecution_; ++i) {
    std::shuffle(distinct_pairs.begin(), distinct_pairs.end(), rng);
    rank_disjoint_set = disjoint_set::RankQuickUnion<int16_t>(kSize_);
    uint16_t previous_size = 0, cycles = 0, change_counter = 0,
             current_size = rank_disjoint_set.GetDistinctBlocks();

    while (current_size > 1) {
      rank_disjoint_set.MergeBlocks(distinct_pairs.at(cycles));

      cycles++;
      current_size = rank_disjoint_set.GetDistinctBlocks();

      if (previous_size != current_size) {
        previous_size = current_size;
        change_counter++;
        if (change_counter % kDelta_)
          continue;

        statistics.at(change_counter / kDelta_)
            .update(cycles, rank_disjoint_set.GetDistinctBlocks(),
                    rank_disjoint_set.GetTotalPathLenght(),
                    rank_disjoint_set.GetFullCompressionTotalPointersUpdates(),
                    rank_disjoint_set.GetPathSplittingTotalPointersUpdates(),
                    rank_disjoint_set.GetPathHalvingPointersUpdates());
      }
    }
  }

  for (auto element : statistics) {
    if (element.counter > kCutoff)
      WriteStatistics(rank_quick_union_statistics_, element);
  }
}
}  // namespace disjoint_set_benchmark