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

namespace b_tree_benchmark {

class BTreeBenchmark : public ::testing::Test {
#ifdef BTREE_BENCHMARK
 protected:
  const uint16_t kNumberExecition_ = 3;

  static std::array<uint32_t, 10000001> keys_;
  std::mt19937 rng_ = std::mt19937(SEED);

  static std::ofstream table_5_replication_;

  void SetUp() override {
    std::shuffle(keys_.begin(), keys_.end(), rng_);
  }

  void TearDown() override {}

  static void SetUpTestSuite() {
    std::iota(keys_.begin(), keys_.end(), 0);

    table_5_replication_.open("benchmark/tree/outputs/table_5_replication.md");
  }

  static void TearDownTestSuite() {
    table_5_replication_.close();
  }
#endif
};

std::array<uint32_t, 10000001> BTreeBenchmark::keys_;
std::ofstream BTreeBenchmark::table_5_replication_;
}  // namespace b_tree_benchmark
