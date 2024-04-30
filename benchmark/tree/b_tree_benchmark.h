#pragma once

#include <gtest/gtest.h>
#include <algorithm>
#include <fstream>
#include <random>
#include <ranges>
#include <string>
#include "disjoint_set.h"
#include "quick_union.h"
#include "rank_union.h"
#include "weight_union.h"

#define SEED 42
#define SIZE 268435456

namespace b_tree_benchmark {

class BTreeBenchmark : public ::testing::Test {
#ifdef BTREE_BENCHMARK
 protected:
  const uint16_t kNumberExecition_ = 20;

  static std::array<uint32_t, SIZE> keys_;
  std::mt19937 rng_ = std::mt19937(SEED);

  static std::ofstream table_5_replication_;
  static std::ofstream split_count_;

  void SetUp() override {
    std::shuffle(keys_.begin(), keys_.end(), rng_);
  }

  void TearDown() override {}

  static void SetUpTestSuite() {
    std::iota(keys_.begin(), keys_.end(), 0);

    table_5_replication_.open("benchmark/tree/outputs/table_5_replication.md");
    split_count_.open("benchmark/tree/outputs/split_count.md");
  }

  static void TearDownTestSuite() {
    table_5_replication_.close();
    split_count_.close();
  }
#endif
};

std::array<uint32_t, SIZE> BTreeBenchmark::keys_;
std::ofstream BTreeBenchmark::table_5_replication_;
std::ofstream BTreeBenchmark::split_count_;
}  // namespace b_tree_benchmark
