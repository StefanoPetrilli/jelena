#pragma once

#include <gtest/gtest.h>
#include <string>
#include "disjoint_set.h"
#include "quick_union.h"
#include "rank_union.h"

namespace disjoint_set_test {
class RankUnionTest : public ::testing::Test {
 protected:
  int16_t size_ = 10;
  disjoint_set::RankUnion<int16_t> rank_disjoint_set_;
  disjoint_set::WeightUnionFullCompression<int16_t> rank_disjoint_FC_set_;
  disjoint_set::WeightUnionPathSplitting<int16_t> rank_disjoint_PS_set_;
  disjoint_set::WeightUnionPathHalving<int16_t> rank_disjoint_PH_set_;

  RankUnionTest()
      : rank_disjoint_set_(size_),
        rank_disjoint_FC_set_(size_),
        rank_disjoint_PS_set_(size_),
        rank_disjoint_PH_set_(size_) {}

  void SetUp() override {}
  void TearDown() override {}
};
}  // namespace disjoint_set_test
