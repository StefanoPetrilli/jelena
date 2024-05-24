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
}  // namespace tree_test