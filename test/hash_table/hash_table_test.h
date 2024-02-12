#pragma once

#include <gtest/gtest.h>
#include <string>
#include "hash_table.h"

namespace hash_table_test {
class HashTableTest : public ::testing::Test {
 protected:
  hash_table::HashTable hash_table;
  void SetUp() override { hash_table = hash_table::HashTable(); }

  void TearDown() override { hash_table.clear(); }
};
}  // namespace hash_table_test
