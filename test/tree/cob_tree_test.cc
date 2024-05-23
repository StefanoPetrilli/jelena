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

TEST_F(COBTreeTest, AfterFirstDimensionIncrease_Returns_CorrectString4) {
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

  auto actual = cob_tree.ToString();
  std::string expected =
      "Data: [ ,45,50, ,51,65, ,70, ,80,81, ,83,90, ,100]\nTree: [80,45,80]";
  EXPECT_EQ(actual, expected);
}
}  // namespace tree_test