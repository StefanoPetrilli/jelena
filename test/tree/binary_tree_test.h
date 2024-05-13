#pragma once

#include <gtest/gtest.h>
#include "binary_tree.h"

namespace tree_test {
class BinaryTreeTest : public ::testing::Test {
 protected:
  tree::BinaryTree<int> empty_tree = tree::BinaryTree<int>();
  void SetUp() override {}
  void TearDown() override {}
};
}  // namespace tree_test