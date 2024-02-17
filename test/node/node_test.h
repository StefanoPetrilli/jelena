#pragma once

#include <gtest/gtest.h>
#include <string>
#include "node.h"

namespace node_test {
class NodeTest : public ::testing::Test {
 protected:
  node::Node<int> no_neighbors_node_ = node::Node(10);
  void SetUp() override {}
  void TearDown() override {}
};
}  // namespace node_test