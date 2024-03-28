#pragma once

#include <gtest/gtest.h>
#include <algorithm>
#include <fstream>
#include <random>
#include <string>
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
  std::vector<std::tuple<uint16_t, uint16_t>> distinct_pairs;
  std::mt19937 rng = std::mt19937(SEED);

  disjoint_set::QuickUnion<uint16_t> quick_union_set_ =
      disjoint_set::QuickUnion<uint16_t>(kSize_);

  disjoint_set::WeightQuickUnion<int16_t> weighted_disjoint_set_ =
      disjoint_set::WeightQuickUnion<int16_t>(kSize_);

  disjoint_set::RankQuickUnion<int16_t> rank_disjoint_set_ =
      disjoint_set::RankQuickUnion<int16_t>(kSize_);

  // static std::ofstream sequence_file_;
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
        "| Number of Blocks | Cycle count | Total Path Lenght | Full Compression TPU | Path Splitting TPU | Path Halving TPU |\n | - "
        "| - | - | - | - | - |\n";

    // sequence_file_.open("benchmark/disjoint_set/outputs/sequence.md");
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
    // sequence_file_.close();
    quick_union_statistics_.close();
    weight_quick_union_statistics_.close();
    rank_quick_union_statistics_.close();
  }

  void WriteStatistics(std::ostream& file, size_t distinct_blocks,
                       int16_t cycles, int16_t total_path_length,
                       int16_t full_compression_total_pointers_update,
                       int16_t path_splitting_total_pointers_update,
                       int16_t path_halving_total_pointers_update) {
    file << distinct_blocks << " |" << cycles << " | " << total_path_length
         << " | " << full_compression_total_pointers_update << " | "
         << path_splitting_total_pointers_update << " | "
         << path_halving_total_pointers_update << " |" << std::endl;
  }
};
}  // namespace disjoint_set_benchmark
