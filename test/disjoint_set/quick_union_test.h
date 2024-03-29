#pragma once

#include <gtest/gtest.h>
#include <string>
#include "disjoint_set.h"
#include "quick_union.h"

namespace disjoint_set_test {
class QuickUnionTest : public ::testing::Test {
 protected:
  uint16_t size_ = 10;
  disjoint_set::QuickUnion<uint16_t> quick_union_set_;
  disjoint_set::QuickUnionFullCompression<uint16_t> quick_union_FC_set_;
  disjoint_set::QuickUnionPathSplitting<uint16_t> quick_union_PS_set_;
  disjoint_set::QuickUnionPathHalving<uint16_t> quick_union_FH_set_;

  QuickUnionTest()
      : quick_union_set_(size_),
        quick_union_FC_set_(size_),
        quick_union_PS_set_(size_),
        quick_union_FH_set_(size_) {}

  void SetUp() override {}
  void TearDown() override {}
};
}  // namespace disjoint_set_test
