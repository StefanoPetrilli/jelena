#pragma once

#include <gtest/gtest.h>
#include "packed_memory_array.h"

namespace array_test {
class PackedMemoryArrayTest : public ::testing::Test {
 protected:
  array::PackedMemoryArray<uint32_t> pma = array::PackedMemoryArray<uint32_t>();

  void SetUp() override {}

  void TearDown() override {}
};
}  // namespace array_test