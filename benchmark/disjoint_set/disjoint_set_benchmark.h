#pragma once

#include <gtest/gtest.h>
#include <algorithm>
#include <fstream>
#include <random>
#include <string>
#include "statistics.h"
#include "disjoint_set.h"
#include "quick_union.h"
#include "rank_quick_union.h"
#include "weight_quick_union.h"

#define SEED 42

namespace disjoint_set_benchmark {
class DisjointSetBenchmark : public ::testing::Test {
 protected:
  const uint16_t kSize_ = 100;
  const uint16_t kDelta_ = 20;
  const uint16_t kNumberExecution_ = 50;
  const uint16_t kCutoff = 5;

  std::vector<std::tuple<uint16_t, uint16_t>> distinct_pairs;
  std::mt19937 rng = std::mt19937(SEED);

  static std::ofstream quick_union_statistics_;
  static std::ofstream weight_quick_union_statistics_;
  static std::ofstream rank_quick_union_statistics_;

  void SetUp() override {
    for (size_t i = 0; i < kSize_; i++)
      for (size_t j = 0; j < kSize_; j++)
        distinct_pairs.push_back(std::make_tuple(i, j));

    std::shuffle(distinct_pairs.begin(), distinct_pairs.end(), rng);
  }
  void TearDown() override {}

  static void SetUpTestSuite() {
    std::string table_head =
        "| Number of Blocks | Cycle count | Total Path length | Full "
        "Compression TPU | Path Splitting TPU | Path Halving TPU |\n | - "
        "| - | - | - | - | - |\n";

    quick_union_statistics_.open(
        "benchmark/disjoint_set/outputs/quick_union.md");
    weight_quick_union_statistics_.open(
        "benchmark/disjoint_set/outputs/weight_quick_union.md");
    rank_quick_union_statistics_.open(
        "benchmark/disjoint_set/outputs/rank_quick_union.md");
    quick_union_statistics_ << table_head;
    weight_quick_union_statistics_ << table_head;
    rank_quick_union_statistics_ << table_head;
  }

  static void TearDownTestSuite() {
    quick_union_statistics_.close();
    weight_quick_union_statistics_.close();
    rank_quick_union_statistics_.close();
  }

  template <typename DisjointSetType>
  void RunBenchmark(std::ofstream& statistics_file) {
    std::vector<Statistics> statistics(kSize_ / kDelta_);
    DisjointSetType disjoint_set(0);

    for (int i = 0; i < kNumberExecution_; ++i) {
      std::shuffle(distinct_pairs.begin(), distinct_pairs.end(), rng);
      disjoint_set = DisjointSetType(kSize_);
      uint16_t previous_size = 0, cycles = 0, change_counter = 0,
               current_size = disjoint_set.GetDistinctBlocks();

      while (current_size > 1) {
        disjoint_set.MergeBlocks(distinct_pairs.at(cycles));

        cycles++;
        current_size = disjoint_set.GetDistinctBlocks();

        if (previous_size != current_size) {
          previous_size = current_size;
          change_counter++;
          if (change_counter % kDelta_)
            continue;

          statistics.at(change_counter / kDelta_)
              .update(cycles, disjoint_set.GetDistinctBlocks(),
                      disjoint_set.GetTotalPathlength(),
                      disjoint_set.GetFullCompressionTotalPointersUpdates(),
                      disjoint_set.GetPathSplittingTotalPointersUpdates(),
                      disjoint_set.GetPathHalvingPointersUpdates());
        }
      }
    }

    for (auto element : statistics) {
      if (element.counter > kCutoff)
        WriteStatistics(statistics_file, element);
    }
  }

  void WriteStatistics(std::ostream& file, Statistics statistics) {
    file << statistics.ToString() << std::endl;
  }
};
}  // namespace disjoint_set_benchmark
