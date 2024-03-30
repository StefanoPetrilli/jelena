#pragma once

#include <gtest/gtest.h>
#include <algorithm>
#include <fstream>
#include <random>
#include <string>
#include <ranges>
#include "disjoint_set.h"
#include "quick_union.h"
#include "rank_union.h"
#include "statistics.h"
#include "weight_union.h"

#define SEED 42

namespace disjoint_set_benchmark {
class DisjointSetBenchmark : public ::testing::Test {
 protected:
  const uint16_t kSize_ = 10001;
  const uint16_t kDelta_ = kSize_ / 10;
  const uint16_t kCutoff_ = 5;
  const uint16_t kNumberExecution_ = 20;
  const uint16_t kEpsilon_ = 2;

  std::vector<std::tuple<uint16_t, uint16_t>> distinct_pairs;
  std::mt19937 rng = std::mt19937(SEED);

  static std::ofstream quick_union_statistics_;
  static std::ofstream quick_union_FC_statistics_;
  static std::ofstream quick_union_PS_statistics_;
  static std::ofstream quick_union_PH_statistics_;
  static std::ofstream weight_union_statistics_;
  static std::ofstream weight_union_FC_statistics_;
  static std::ofstream weight_union_PS_statistics_;
  static std::ofstream weight_union_PH_statistics_;
  static std::ofstream rank_union_statistics_;
  static std::ofstream rank_union_FC_statistics_;
  static std::ofstream rank_union_PS_statistics_;
  static std::ofstream rank_union_PH_statistics_;

  void SetUp() override {
    distinct_pairs.reserve(kSize_ * kSize_);
    for (auto i : std::views::iota(0u, kSize_)) {
      for (auto j : std::views::iota(0u, kSize_)) {
        if (i == j) continue;
        distinct_pairs.emplace_back(i, j);
      }
    }
  }

  void TearDown() override {}

  static void SetUpTestSuite() {
    std::string table_head =
        "| Number of Blocks | Cycle count | TPL | TPU | Normalized TPL | "
        "Normalized TPU | Total Cost | Normalized Total Cost |\n"
        "| - | - | - | - | - | - | - | - |\n";

    quick_union_statistics_.open(
        "benchmark/disjoint_set/outputs/quick_union.md");
    quick_union_FC_statistics_.open(
        "benchmark/disjoint_set/outputs/quick_union_FC.md");
    quick_union_PS_statistics_.open(
        "benchmark/disjoint_set/outputs/quick_union_PS.md");
    quick_union_PH_statistics_.open(
        "benchmark/disjoint_set/outputs/quick_union_PH.md");
    weight_union_statistics_.open(
        "benchmark/disjoint_set/outputs/weight_union.md");
    weight_union_FC_statistics_.open(
        "benchmark/disjoint_set/outputs/weight_union_FC.md");
    weight_union_PS_statistics_.open(
        "benchmark/disjoint_set/outputs/weight_union_PS.md");
    weight_union_PH_statistics_.open(
        "benchmark/disjoint_set/outputs/weight_union_PH.md");
    rank_union_statistics_.open("benchmark/disjoint_set/outputs/rank_union.md");
    rank_union_FC_statistics_.open(
        "benchmark/disjoint_set/outputs/rank_union_FC.md");
    rank_union_PS_statistics_.open(
        "benchmark/disjoint_set/outputs/rank_union_PS.md");
    rank_union_PH_statistics_.open(
        "benchmark/disjoint_set/outputs/rank_union_PH.md");

    quick_union_statistics_ << table_head;
    quick_union_FC_statistics_ << table_head;
    quick_union_PS_statistics_ << table_head;
    quick_union_PH_statistics_ << table_head;
    weight_union_statistics_ << table_head;
    weight_union_FC_statistics_ << table_head;
    weight_union_PS_statistics_ << table_head;
    weight_union_PH_statistics_ << table_head;
    rank_union_statistics_ << table_head;
    rank_union_FC_statistics_ << table_head;
    rank_union_PS_statistics_ << table_head;
    rank_union_PH_statistics_ << table_head;
  }

  static void TearDownTestSuite() {
    quick_union_statistics_.close();
    quick_union_FC_statistics_.close();
    quick_union_PS_statistics_.close();
    quick_union_PH_statistics_.close();
    weight_union_statistics_.close();
    weight_union_FC_statistics_.close();
    weight_union_PS_statistics_.close();
    weight_union_PH_statistics_.close();
    rank_union_statistics_.close();
    rank_union_FC_statistics_.close();
    rank_union_PS_statistics_.close();
    rank_union_PH_statistics_.close();
  }

  template <typename DisjointSetType>
  void RunBenchmark(std::ofstream& statistics_file, bool isFC = false) {
    std::vector<Statistics> statistics((kSize_ / kDelta_) + 1);
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
              .Update(cycles, disjoint_set.GetDistinctBlocks(),
                      disjoint_set.GetTotalPathlength(),
                      disjoint_set.GetTotalPointersUpdates());
        }
      }
    }

    for (auto element : statistics) {
      if (element.counter > kCutoff_)
        WriteStatistics(statistics_file, element, this->kSize_, this->kEpsilon_,
                        isFC);
    }
  }

  void WriteStatistics(std::ostream& file, Statistics statistics,
                       int32_t normalization_size, int16_t epsilon, bool isFC) {
    file << statistics.ToString(normalization_size, epsilon, isFC) << std::endl;
  }
};
}  // namespace disjoint_set_benchmark
