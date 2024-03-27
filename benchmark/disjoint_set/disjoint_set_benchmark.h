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
  uint16_t size_ = 100;
  std::vector<std::tuple<uint16_t, uint16_t>> distinct_pairs;
  std::mt19937 rng = std::mt19937(SEED);

  disjoint_set::QuickUnion<uint16_t> quick_union_set_ =
      disjoint_set::QuickUnion<uint16_t>(size_);

  disjoint_set::WeightQuickUnion<int16_t> weighted_disjoint_set_ =
      disjoint_set::WeightQuickUnion<int16_t>(size_);

  disjoint_set::RankQuickUnion<int16_t> rank_disjoint_set_ =
      disjoint_set::RankQuickUnion<int16_t>(size_);

  void SetUp() override {
    for (size_t i = 0; i < size_; i++)
      for (size_t j = 0; j < size_; j++)
        distinct_pairs.push_back(std::make_tuple(i, j));

    std::shuffle(distinct_pairs.begin(), distinct_pairs.end(), rng);
  }
  void TearDown() override {}
};
}  // namespace disjoint_set_benchmark
