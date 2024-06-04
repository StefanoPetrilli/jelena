#pragma once

#include <gtest/gtest.h>
#include <algorithm>
#include <fstream>
#include <random>
#include <ranges>
#include <string>

#define SEED 42
#define SIZE 4294967294

namespace cob_tree_benchmark {

class COBTreeBenchmark : public ::testing::Test {
  static std::ofstream big_tree;
#ifdef COBTREE_BENCHMARK
 protected:
  const uint16_t kNumberExecition_ = 5;

  std::mt19937 rng_ = std::mt19937(SEED);
  std::uniform_int_distribution<uint32_t> dist_{0, SIZE};

  void SetUp() override {}

  void TearDown() override {}

  static void SetUpTestSuite() {
    big_tree.open("benchmark/tree/outputs/big.md");
  }

  static void TearDownTestSuite() { big_tree.close(); }
#endif
};

std::ofstream COBTreeBenchmark::big_tree;
}  // namespace cob_tree_benchmark
