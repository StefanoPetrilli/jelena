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
  std::string expected = "50, ,70,80";
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
  std::string expected = "50, ,65,70,80, ,90, ";
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
  std::string expected = "50, ,65,70,80, ,85,90";
  EXPECT_EQ(actual, expected);
}

TEST_F(PackedMemoryArrayTest,
       AfterInserting7Values_Returns_OrderedValuesString) {
  pma.Insert(80);
  pma.Insert(50);
  pma.Insert(70);
  pma.Insert(90);
  pma.Insert(65);
  pma.Insert(85);
  pma.Insert(10);

  auto actual = pma.ToString();
  std::string expected = "10,50,65,70,80, ,85,90";
  EXPECT_EQ(actual, expected);
}

TEST_F(PackedMemoryArrayTest,
       AfterInserting8Values_Returns_OrderedValuesString) {
  pma.Insert(80);
  pma.Insert(50);
  pma.Insert(70);
  pma.Insert(90);
  pma.Insert(65);
  pma.Insert(85);
  pma.Insert(10);
  pma.Insert(21);

  auto actual = pma.ToString();
  std::string expected = "10, ,21, ,50, ,65,70,80, ,85, ,90, , , ";
  EXPECT_EQ(actual, expected);
}

TEST_F(PackedMemoryArrayTest,
       AfterInsertingValues_Returns_OrderedValuesString) {
  pma.Insert(80);
  pma.Insert(50);
  pma.Insert(70);
  pma.Insert(90);
  pma.Insert(65);
  pma.Insert(85);
  pma.Insert(10);
  pma.Insert(21);
  pma.Insert(30);
  pma.Insert(20);
  pma.Insert(5);
  pma.Insert(13);

  auto actual = pma.ToString();
  std::string expected = "5, ,10, ,13,20,21,30,50,65,70,80, ,85, ,90";
  EXPECT_EQ(actual, expected);
}

TEST_F(PackedMemoryArrayTest,
       AfterInsertingValues_Returns_OrderedValuesString2) {
  pma.Insert(80);
  pma.Insert(50);
  pma.Insert(70);
  pma.Insert(90);
  pma.Insert(65);
  pma.Insert(85);
  pma.Insert(10);
  pma.Insert(100);
  pma.Insert(110);
  pma.Insert(120);
  pma.Insert(95);
  pma.Insert(105);
  pma.Insert(125);

  auto actual = pma.ToString();
  std::string expected = "10, ,50, ,65,70,80,85,90, ,95,100,105,110,120,125";
  EXPECT_EQ(actual, expected);
}

TEST_F(PackedMemoryArrayTest,
       AfterInsertingValues_Returns_OrderedValuesString3) {
  pma.Insert(80);
  pma.Insert(50);
  pma.Insert(70);
  pma.Insert(90);
  pma.Insert(65);
  pma.Insert(85);
  pma.Insert(10);
  pma.Insert(21);
  pma.Insert(30);
  pma.Insert(20);
  pma.Insert(5);
  pma.Insert(13);
  pma.Insert(100);
  pma.Insert(95);
  pma.Insert(97);

  auto actual = pma.ToString();
  std::string expected =
      "5, ,10, ,13, ,20, ,21, ,30, ,50, ,65, ,70, ,80, ,85, ,90, ,95, ,97, "
      ",100, , , ";
  EXPECT_EQ(actual, expected);
}

TEST_F(PackedMemoryArrayTest,
       ForCycleInsert100_Returns_OrderedValuesString) {
  for (size_t i = 0; i <= 100; i++)
    pma.Insert(i);

  auto actual = pma.ToString();
  std::string expected =
      "1, ,2, ,3, ,4, ,5, ,6, ,7, ,8, ,9, ,10, ,11, ,12, ,13, ,14, ,15, ,16, "
      ",17, ,18, ,19, ,20, ,21, ,22, ,23, ,24, ,25, ,26, ,27, ,28, ,29, ,30, "
      ",31, ,32, ,33, ,34, ,35, ,36, ,37, ,38, ,39, ,40, ,41, ,42, ,43, ,44, "
      ",45, ,46, ,47, ,48, ,49, ,50, ,51, ,52, ,53, ,54, ,55, ,56, ,57, ,58, "
      ",59, ,60, ,61, ,62, ,63, ,64, ,65, ,66, ,67, ,68, ,69, ,70, ,71, ,72, "
      ",73, ,74, ,75, ,76, ,77, ,78, ,79, ,80, ,81, ,82, ,83, ,84, ,85, ,86, "
      ",87, ,88, ,89, ,90, ,91, ,92, , , , , , , , , , , , , , , , , , , , , , "
      ", , , , , , , , , , , , , , , , , , , , , , , , , , , , , , , , , , , "
      ",93, ,94, ,95, ,96, ,97, ,98, ,99, ,100, ";
  EXPECT_EQ(actual, expected);
}

TEST_F(PackedMemoryArrayTest,
       ReverseForCycleInsert100_Returns_OrderedValuesString) {
  for (size_t i = 101; i >= 1; i--)
    pma.Insert(i);

  auto actual = pma.ToString();
  std::string expected =
      "1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22, ,23, ,24, "
      ",25, ,26, ,27, ,28, , ,29, , ,30, , ,31, , ,32, , ,33, , ,34, , ,35, , "
      ",36, , ,37, , ,38, , ,39, , ,40, , ,41, , ,42, , ,43, , ,44, , ,45, , "
      ",46, , ,47, , ,48, , ,49, , ,50, , ,51, , ,52, , ,53, , ,54, , ,55, , "
      ",56, , ,57, , ,58, , ,59, , ,60, , ,61, , ,62, , ,63, , ,64, , ,65, , "
      ",66, , ,67, , ,68, , ,69, , ,70, , ,71, , ,72, , ,73, , ,74, , ,75, , "
      ",76, , ,77, , ,78, , ,79, , ,80, , ,81, , ,82, , ,83, , ,84, , ,85, , "
      ",86, , ,87, , ,88, , ,89, , ,90, , ,91, , ,92, , ,93, , ,94, , ,95, , "
      ",96, , ,97, , ,98, , ,99, , ,100, , ,101, , , ";
  EXPECT_EQ(actual, expected);
}

}  // namespace array_test