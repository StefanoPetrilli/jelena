#pragma once

#include <gtest/gtest.h>
#include <string>
#include "linked_list.h"

namespace linked_list_test {
class LinkedListTest : public ::testing::Test {
 protected:
  linked_list::LinkedList<int> linked_list_;
  void SetUp() override { linked_list_ = linked_list::LinkedList<int>(); }
  void TearDown() override { linked_list_; }
};
}  // namespace linked_list_test
