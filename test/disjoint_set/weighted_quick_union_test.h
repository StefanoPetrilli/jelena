#pragma once

#include <gtest/gtest.h>
#include <limits>
#include <string>
#include "disjoint_set.h"
#include "quick_union.h"
#include "weight_quick_union.h"

namespace disjoint_set_test {
class WeightQuickUnion : public ::testing::Test {
 protected:
  int16_t size_ = std::numeric_limits<int16_t>::max() / 2;
  disjoint_set::WeightQuickUnion<int16_t> weighted_disjoint_set_ =
      disjoint_set::WeightQuickUnion<int16_t>(size_);

  void SetUp() override {}
  void TearDown() override {}
};
}  // namespace disjoint_set_test
