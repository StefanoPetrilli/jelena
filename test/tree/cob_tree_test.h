#pragma once

#include <gtest/gtest.h>
#include "cob_tree.h"

namespace tree_test {
class COBTreeTest : public ::testing::Test {
 protected:
  tree::COBTree<int> cob_tree = tree::COBTree<int>();
  void SetUp() override {}
  void TearDown() override {}
};
}  // namespace tree_test