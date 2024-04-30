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
#define SIZE 4294967294

namespace b_tree_benchmark {

class BTreeBenchmark : public ::testing::Test {
#ifdef BTREE_BENCHMARK
 protected:
  const uint16_t kNumberExecition_ = 5;

  std::mt19937 rng_ = std::mt19937(SEED);
  std::uniform_int_distribution<uint32_t> dist_{0, SIZE};

  static std::ofstream table_5_replication_;
  static std::ofstream split_count_;
  static std::ofstream split_count_unbalanced_;

  void SetUp() override {
  }

  void TearDown() override {}

  static void SetUpTestSuite() {
    table_5_replication_.open("benchmark/tree/outputs/table_5_replication.md");
    split_count_.open("benchmark/tree/outputs/split_count.md");
    split_count_unbalanced_.open("benchmark/tree/outputs/split_count_unbalanced.md");
  }

  static void TearDownTestSuite() {
    table_5_replication_.close();
    split_count_.close();
    split_count_unbalanced_.close();
  }
#endif
};

std::ofstream BTreeBenchmark::table_5_replication_;
std::ofstream BTreeBenchmark::split_count_;
std::ofstream BTreeBenchmark::split_count_unbalanced_;
}  // namespace b_tree_benchmark
