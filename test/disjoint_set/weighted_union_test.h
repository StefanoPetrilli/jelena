#pragma once

#include <gtest/gtest.h>
#include <string>
#include "disjoint_set.h"
#include "quick_union.h"
#include "weight_union.h"

namespace disjoint_set_test {
class WeightUnion : public ::testing::Test {
 protected:
  int16_t size_ = 10;
  disjoint_set::WeightUnion<int16_t> weighted_disjoint_set_ =
      disjoint_set::WeightUnion<int16_t>(size_);

  void SetUp() override {}
  void TearDown() override {}
};
}  // namespace disjoint_set_test
