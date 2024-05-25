#pragma once

#include <gtest/gtest.h>
#include "cob_tree.h"

namespace tree_test {
class COBTreeTest : public ::testing::Test {
 protected:
  tree::COBTree<uint32_t> cob_tree = tree::COBTree<uint32_t>();
  tree::COBTree<uint32_t> cob_tree_even = tree::COBTree<uint32_t>();
  tree::COBTree<uint32_t> cob_tree_big = tree::COBTree<uint32_t>();

  void SetUp() override {
    for (uint32_t i = 2; i < 64; i += 2)
      cob_tree_even.Insert(i);
  }

  void TearDown() override {}
};
}  // namespace tree_test