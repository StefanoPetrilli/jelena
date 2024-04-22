#pragma once

#include <gtest/gtest.h>
#include "b_tree.h"

namespace tree_test {
class BTreeTest : public ::testing::Test {
 protected:
  tree::BTree<uint16_t> empty_tree_order_5 = tree::BTree<uint16_t>(5);
  tree::BTree<uint16_t> empty_tree_order_4 = tree::BTree<uint16_t>(4);
  tree::BTree<uint16_t> empty_tree_order_3 = tree::BTree<uint16_t>(3);

  void SetUp() override {}

  void TearDown() override {}
};
}  // namespace tree_test