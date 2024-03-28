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
  const uint16_t kNumberExecution_ = 50;
  const uint16_t kCutoff = 5;

  std::vector<std::tuple<uint16_t, uint16_t>> distinct_pairs;
  std::mt19937 rng = std::mt19937(SEED);

  static std::ofstream quick_union_statistics_;
  static std::ofstream weight_quick_union_statistics_;
  static std::ofstream rank_quick_union_statistics_;

  struct Statistics {
    int16_t distinct_blocks;
    int16_t cycles;
    int16_t total_path_length;
    int16_t full_compression_total_pointers_update;
    int16_t path_splitting_total_pointers_update;
    int16_t path_halving_total_pointers_update;
    int16_t counter;

    Statistics()
        : distinct_blocks(0),
          cycles(0),
          total_path_length(0),
          full_compression_total_pointers_update(0),
          path_splitting_total_pointers_update(0),
          path_halving_total_pointers_update(0),
          counter(0) {}

    void update(int16_t cycles, int16_t distinct_blocks,
                int16_t total_path_length,
                int16_t full_compression_total_pointers_update,
                int16_t path_splitting_total_pointers_update,
                int16_t path_halving_total_pointers_update) {
      this->cycles += cycles;
      this->distinct_blocks += distinct_blocks;
      this->total_path_length += total_path_length;
      this->full_compression_total_pointers_update +=
          full_compression_total_pointers_update;
      this->path_splitting_total_pointers_update +=
          path_splitting_total_pointers_update;
      this->path_halving_total_pointers_update +=
          path_halving_total_pointers_update;
      this->counter++;
    }
  };

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

  void WriteStatistics(std::ostream& file, Statistics statistics) {
    file << statistics.distinct_blocks / statistics.counter << " |"
         << statistics.cycles / statistics.counter << " | "
         << statistics.total_path_length / statistics.counter << " | "
         << statistics.full_compression_total_pointers_update /
                statistics.counter
         << " | "
         << statistics.path_splitting_total_pointers_update / statistics.counter
         << " | "
         << statistics.path_halving_total_pointers_update / statistics.counter
         << " |" << std::endl;
  }
};
}  // namespace disjoint_set_benchmark
