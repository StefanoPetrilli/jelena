#include "cob_tree_test.h"

namespace tree_test {

TEST_F(COBTreeTest, EmptyPackedArray_Returns_EmptyString) {
  auto actual = cob_tree.ToString();
  std::string expected = "Data: [ , , , ]\nTree: [ ]";
  EXPECT_EQ(actual, expected);
}

TEST_F(COBTreeTest, InsertFirstBlock_Returns_CorrectString) {
  cob_tree.Insert(80);
  cob_tree.Insert(50);
  cob_tree.Insert(70);
  cob_tree.Insert(90);

  auto actual = cob_tree.ToString();
  std::string expected = "Data: [50,70,80,90]\nTree: [50]";
  EXPECT_EQ(actual, expected);
}

TEST_F(COBTreeTest, AfterFirstDimensionIncrease_Returns_CorrectString) {
  cob_tree.Insert(80);
  cob_tree.Insert(50);
  cob_tree.Insert(70);
  cob_tree.Insert(90);
  cob_tree.Insert(65);

  auto actual = cob_tree.ToString();
  std::string expected = "Data: [ ,50,65,70,80, ,90, ]\nTree: [80,50,80]";
  EXPECT_EQ(actual, expected);
}

TEST_F(COBTreeTest, AfterFirstDimensionIncrease_Returns_CorrectString2) {
  cob_tree.Insert(80);
  cob_tree.Insert(50);
  cob_tree.Insert(70);
  cob_tree.Insert(90);
  cob_tree.Insert(100);

  auto actual = cob_tree.ToString();
  std::string expected = "Data: [50, ,70, , ,80,90,100]\nTree: [80,50,80]";
  EXPECT_EQ(actual, expected);
}

TEST_F(COBTreeTest, AfterFirstDimensionIncrease_Returns_CorrectString3) {
  cob_tree.Insert(80);
  cob_tree.Insert(50);
  cob_tree.Insert(70);
  cob_tree.Insert(90);
  cob_tree.Insert(65);
  cob_tree.Insert(51);
  cob_tree.Insert(81);
  cob_tree.Insert(100);
  cob_tree.Insert(83);

  auto actual = cob_tree.ToString();
  std::string expected =
      "Data: [50, ,51, ,65, ,70, , ,80,81, ,83,90, ,100]\nTree: [80,50,80]";
  EXPECT_EQ(actual, expected);
}

TEST_F(COBTreeTest, AfterFirstDimensionIncrease_Returns_CorrectString5) {
  cob_tree.Insert(80);
  cob_tree.Insert(50);
  cob_tree.Insert(70);
  cob_tree.Insert(90);
  cob_tree.Insert(65);
  cob_tree.Insert(51);
  cob_tree.Insert(81);
  cob_tree.Insert(100);
  cob_tree.Insert(83);
  cob_tree.Insert(45);
  cob_tree.Insert(10);
  cob_tree.Insert(5);
  cob_tree.Insert(4);
  cob_tree.Insert(6);

  auto actual = cob_tree.ToString();
  std::string expected =
      "Data: [ ,4,5, ,6,10, ,45, ,50, , ,51, ,65, , ,70, ,80, , ,81, ,83, , "
      ",90, ,100, , ]\nTree: [70,50,4,50,83,70,83]";
  EXPECT_EQ(actual, expected);
}

TEST_F(COBTreeTest, AfterFirstDimensionIncrease_Returns_CorrectString6) {
  cob_tree.Insert(80);
  cob_tree.Insert(50);
  cob_tree.Insert(70);
  cob_tree.Insert(90);
  cob_tree.Insert(65);
  cob_tree.Insert(51);
  cob_tree.Insert(81);
  cob_tree.Insert(100);
  cob_tree.Insert(83);
  cob_tree.Insert(45);
  cob_tree.Insert(10);
  cob_tree.Insert(5);
  cob_tree.Insert(4);
  cob_tree.Insert(2);

  auto actual = cob_tree.ToString();
  std::string expected =
      "Data: [ ,2,4, ,5,10, ,45, ,50, , ,51, ,65, , ,70, ,80, , ,81, ,83, , "
      ",90, ,100, , ]\nTree: [70,50,2,50,83,70,83]";
  EXPECT_EQ(actual, expected);
}

TEST_F(COBTreeTest, AfterFirstDimensionIncrease_Returns_CorrectString7) {
  cob_tree.Insert(80);
  cob_tree.Insert(50);
  cob_tree.Insert(70);
  cob_tree.Insert(90);
  cob_tree.Insert(65);
  cob_tree.Insert(51);
  cob_tree.Insert(81);
  cob_tree.Insert(100);
  cob_tree.Insert(83);
  cob_tree.Insert(45);
  cob_tree.Insert(10);
  cob_tree.Insert(5);
  cob_tree.Insert(4);
  cob_tree.Insert(2);
  cob_tree.Insert(101);

  auto actual = cob_tree.ToString();
  std::string expected =
      "Data: [ ,2,4, ,5,10, ,45, ,50, , ,51, ,65, , ,70, ,80, , ,81, , ,83, "
      ",90, ,100, ,101]\nTree: [70,50,2,50,83,70,83]";
  EXPECT_EQ(actual, expected);
}

TEST_F(COBTreeTest, AfterFirstDimensionIncrease_Returns_CorrectString8) {
  cob_tree.Insert(80);
  cob_tree.Insert(50);
  cob_tree.Insert(70);
  cob_tree.Insert(90);
  cob_tree.Insert(65);
  cob_tree.Insert(51);
  cob_tree.Insert(81);
  cob_tree.Insert(100);
  cob_tree.Insert(83);
  cob_tree.Insert(45);
  cob_tree.Insert(10);
  cob_tree.Insert(5);
  cob_tree.Insert(4);
  cob_tree.Insert(2);
  cob_tree.Insert(101);
  cob_tree.Insert(49);
  cob_tree.Insert(1);
  cob_tree.Insert(6);
  cob_tree.Insert(20);

  auto actual = cob_tree.ToString();
  std::string expected =
      "Data: [ ,1,2,4,5,6,10,20, ,45,49,50, ,51,65, , ,70, ,80, , ,81, , ,83, "
      ",90, ,100, ,101]\nTree: [70,45,1,45,83,70,83]";
  EXPECT_EQ(actual, expected);
}

TEST_F(COBTreeTest, AfterFirstDimensionIncrease_Returns_CorrectString9) {
  cob_tree.Insert(80);
  cob_tree.Insert(50);
  cob_tree.Insert(70);
  cob_tree.Insert(90);
  cob_tree.Insert(65);
  cob_tree.Insert(51);
  cob_tree.Insert(81);
  cob_tree.Insert(100);
  cob_tree.Insert(83);
  cob_tree.Insert(45);
  cob_tree.Insert(10);
  cob_tree.Insert(5);
  cob_tree.Insert(4);
  cob_tree.Insert(2);
  cob_tree.Insert(101);
  cob_tree.Insert(49);
  cob_tree.Insert(1);
  cob_tree.Insert(6);
  cob_tree.Insert(20);
  cob_tree.Insert(82);
  cob_tree.Insert(84);
  cob_tree.Insert(85);
  cob_tree.Insert(86);
  cob_tree.Insert(87);
  cob_tree.Insert(88);

  auto actual = cob_tree.ToString();
  std::string expected =
      "Data: [ ,1,2,4,5,6,10,20, ,45,49,50, ,51,65, , ,70,80,81, ,82,83,84, "
      ",85,86,87,88,90,100,101]\nTree: [70,45,1,45,85,70,85]";
  EXPECT_EQ(actual, expected);
}

TEST_F(COBTreeTest, AfterFirstDimensionIncrease_Returns_CorrectString10) {
  for (uint i = 1; i <= 25; i++)
    cob_tree.Insert(i);

  auto actual = cob_tree.ToString();
  std::string expected =
      "Data: [1, ,2, , ,3, , ,4, ,5, , ,6, , ,7, ,8, , ,9, , ,10, ,11, , ,12, "
      ", ,13, ,14, , ,15, , ,16, ,17, , ,18, , ,19, ,20, , ,21, , , ,22, ,23, "
      ",24, ,25]\nTree: [13,7,19,4,1,4,10,7,10,16,13,16,22,19,22]";
  EXPECT_EQ(actual, expected);
}

TEST_F(COBTreeTest, AfterFirstDimensionIncrease_Returns_CorrectString11) {
  for (uint i = 1; i <= 100; i++)
    cob_tree.Insert(i);

  auto actual = cob_tree.ToString();
  std::string expected =
      "Data: [1, ,2, , ,3, , ,4, , ,5, , ,6, , ,7, ,8, , ,9, , ,10, , ,11, , "
      ",12, , ,13, ,14, , ,15, , ,16, , ,17, , ,18, , ,19, , ,20, ,21, , ,22, "
      ", ,23, , ,24, , ,25, , ,26, ,27, , ,28, , ,29, , ,30, , ,31, , ,32, , "
      ",33, ,34, , ,35, , ,36, , ,37, , ,38, , ,39, ,40, , ,41, , ,42, , ,43, "
      ", ,44, , ,45, , ,46, ,47, , ,48, , ,49, , ,50, , ,51, , ,52, ,53, , "
      ",54, , ,55, , ,56, , ,57, , ,58, ,59, , ,60, , ,61, , ,62, , ,63, , "
      ",64, , ,65, ,66, , ,67, , ,68, , ,69, , ,70, , ,71, ,72, , ,73, , ,74, "
      ", ,75, , ,76, , ,77, , ,78, ,79, , ,80, , ,81, , ,82, , ,83, , ,84, "
      ",85, , ,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100]\nTree: "
      "[46,24,13,35,69,58,80,7,1,7,18,13,18,30,24,30,41,35,41,52,46,52,63,58,"
      "63,75,69,75,86,80,86]";
  EXPECT_EQ(actual, expected);
}

TEST_F(COBTreeTest, AfterFirstDimensionIncrease_Returns_CorrectString12) {
  for (uint i = 100; i >= 1; i--)
    cob_tree.Insert(i);

  auto actual = cob_tree.ToString();
  std::string expected =
      "Data: [ ,1,2,3,4,5,6,7, ,8,9,10,11,12,13,14,15,16,17,18,19, "
      ",20,21,22,23,24,25, ,26,27,28, ,29, , , ,30, , ,31, , ,32, , ,33, , "
      ",34, , ,35, , ,36, , ,37, , ,38, , ,39, , ,40, , ,41, , , ,42, , ,43, , "
      ",44, , ,45, , ,46, , ,47, , ,48, , ,49, , ,50, , ,51, , ,52, , ,53, , , "
      ",54, , ,55, , ,56, , ,57, , ,58, , ,59, , ,60, , ,61, , ,62, , ,63, , "
      ",64, , ,65, , , ,66, , ,67, , ,68, , ,69, , ,70, , ,71, , ,72, , ,73, , "
      ",74, , ,75, , ,76, , ,77, , , ,78, , ,79, , ,80, , ,81, , ,82, , ,83, , "
      ",84, , ,85, , ,86, , ,87, , ,88, , ,89, , , ,90, , ,91, , ,92, , ,93, , "
      ",94, , ,95, , ,96, , ,97, , ,98, , ,99, , ,100, , , ]\nTree: "
      "[60,39,29,50,81,70,91,15,1,15,34,29,34,44,39,44,55,50,55,65,60,65,76,70,"
      "76,86,81,86,96,91,96]";
  EXPECT_EQ(actual, expected);
}

TEST_F(COBTreeTest, EvenTreeContainsEven_Returns_True) {
  for (uint32_t i = 2; i < 64; i += 2)
    EXPECT_EQ(cob_tree_even.Contains(i), true);
}

TEST_F(COBTreeTest, EvenTreeContainsOdd_Returns_False) {
  for (uint32_t i = 1; i < 64; i += 2)
    EXPECT_EQ(cob_tree_even.Contains(i), false);
}
}  // namespace tree_test