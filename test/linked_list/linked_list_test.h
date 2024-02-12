#pragma once

#include <gtest/gtest.h>
#include <string>
#include "linked_list.h"

namespace linked_list_test {
class LinkedListTest : public ::testing::Test {
 protected:
  linked_list::LinkedList<int> _linked_list;
  void SetUp() override { _linked_list = linked_list::LinkedList<int>(); }

  void TearDown() override { _linked_list.Clear(); }
};
}  // namespace linked_list_test
