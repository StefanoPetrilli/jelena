#pragma once

#include <gtest/gtest.h>
#include <limits>
#include <string>
#include "disjoint_set.h"
#include "quick_union.h"

namespace disjoint_set_test {
class DisjointSetTest : public ::testing::Test {
 protected:
  disjoint_set::QuickUnion<uint16_t> disjoint_set_ =
      disjoint_set::QuickUnion<uint16_t>(std::numeric_limits<uint16_t>::max());
  void SetUp() override {}
  void TearDown() override {}
};
}  // namespace disjoint_set_test
