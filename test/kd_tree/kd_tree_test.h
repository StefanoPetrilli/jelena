#pragma once

#include <gtest/gtest.h>
#include <iostream>
#include <sstream>
#include <string>
#include "kd_tree.h"

namespace kd_tree_test {

class KdTreeTest : public ::testing::Test {
 protected:
  kd_tree::KdTree<uint16_t> kd_tree_;
  void SetUp() override {
    kd_tree_ = kd_tree::KdTree<uint16_t>();
  }
  void TearDown() override {}
};
}  // namespace kd_tree_test
