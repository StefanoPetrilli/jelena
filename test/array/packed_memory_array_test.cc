#include "packed_memory_array_test.h"

namespace array_test {

TEST_F(PackedMemoryArrayTest, EmptyPackedArray_Returns_EmptyString) {
  auto actual = pma.ToString();
  std::string expected = " , ";
  EXPECT_EQ(actual, expected);
}

TEST_F(PackedMemoryArrayTest,
       AfterInserting1Value_Returns_OrderedValuesString) {
  pma.Insert(55);
  auto actual = pma.ToString();
  std::string expected = "55, ";
  EXPECT_EQ(actual, expected);
}

TEST_F(PackedMemoryArrayTest,
       AfterInserting2Values_Returns_OrderedValuesString) {
  pma.Insert(99);
  pma.Insert(55);
  auto actual = pma.ToString();
  std::string expected = "55,99";
  EXPECT_EQ(actual, expected);
}

TEST_F(PackedMemoryArrayTest,
       AfterInserting3Values_Returns_OrderedValuesString) {
  pma.Insert(80);
  pma.Insert(50);
  pma.Insert(70);
  auto actual = pma.ToString();
  std::string expected = "50,70,80, ";
  EXPECT_EQ(actual, expected);
}

TEST_F(PackedMemoryArrayTest,
       AfterInserting4Values_Returns_OrderedValuesString) {
  pma.Insert(80);
  pma.Insert(50);
  pma.Insert(70);
  pma.Insert(90);
  auto actual = pma.ToString();
  std::string expected = "50,70,80,90";
  EXPECT_EQ(actual, expected);
}

TEST_F(PackedMemoryArrayTest,
       AfterInserting5Values_Returns_OrderedValuesString) {
  pma.Insert(80);
  pma.Insert(50);
  pma.Insert(70);
  pma.Insert(90);
  pma.Insert(65);

  auto actual = pma.ToString();
  std::string expected = "50,65,70, ,80, ,90, ";
  EXPECT_EQ(actual, expected);
}

TEST_F(PackedMemoryArrayTest,
       AfterInserting6Values_Returns_OrderedValuesString) {
  pma.Insert(80);
  pma.Insert(50);
  pma.Insert(70);
  pma.Insert(90);
  pma.Insert(65);
  pma.Insert(85);

  auto actual = pma.ToString();
  std::string expected = "50,65,70, ,80,85,90, ";
  EXPECT_EQ(actual, expected);
}
}  // namespace array_test