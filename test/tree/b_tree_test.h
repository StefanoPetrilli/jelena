#pragma once

#include <gtest/gtest.h>
#include "b_tree.h"

namespace tree_test {
class BTreeTest : public ::testing::Test {
 protected:
  tree::BTree<uint16_t> empty_tree = tree::BTree<uint16_t>(5);
  void SetUp() override {}
  void TearDown() override {}
};
}  // namespace tree_test