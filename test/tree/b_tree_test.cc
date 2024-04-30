#include "b_tree_test.h"

namespace tree_test {

TEST_F(BTreeTest, EmptyTree_GetOrder_ReturnsOrder) {
  EXPECT_EQ(empty_tree_order_5.GetOrder(), 5);
}

TEST_F(BTreeTest, EmptyTree_IsEmpty_ReturnsTrue) {
  EXPECT_TRUE(empty_tree_order_5.IsEmpty());
}

TEST_F(BTreeTest, EmptyTreeAfterInsert_IsEmpty_ReturnsFalse) {
  empty_tree_order_5.Insert(0);
  EXPECT_FALSE(empty_tree_order_5.IsEmpty());
}

TEST_F(BTreeTest, EmptyTree_ToString_ReturnsExpectedString) {
  auto actual = empty_tree_order_5.ToString();
  std::string expected = "()";

  EXPECT_EQ(actual, expected);
}

TEST_F(BTreeTest, EmptyTreeInsertFirstNode_ToString_ReturnsExpectedString) {
  empty_tree_order_5.Insert(0);
  empty_tree_order_5.Insert(1);
  empty_tree_order_5.Insert(2);
  empty_tree_order_5.Insert(3);
  auto actual = empty_tree_order_5.ToString();
  std::string expected = "(0, 1, 2, 3)";

  EXPECT_EQ(actual, expected);
}

TEST_F(BTreeTest, AfterSplit_ToString_ReturnsExpectedString) {
  empty_tree_order_3.Insert(50);
  empty_tree_order_3.Insert(25);
  empty_tree_order_3.Insert(75);
  auto actual = empty_tree_order_3.ToString();
  std::string expected = "(25)(50)(75)";
  EXPECT_EQ(actual, expected);
}

TEST_F(BTreeTest, AfterMultipleSplit_ToString_ReturnsExpectedString) {
  empty_tree_order_3.Insert(50);
  empty_tree_order_3.Insert(25);
  empty_tree_order_3.Insert(75);
  empty_tree_order_3.Insert(30);
  empty_tree_order_3.Insert(40);
  auto actual = empty_tree_order_3.ToString();
  std::string expected = "(25)(30, 50)(40)(75)";
  EXPECT_EQ(actual, expected);
}

TEST_F(BTreeTest, AfterTwoSplit_ToString_ReturnsExpectedString) {
  empty_tree_order_3.Insert(50);
  empty_tree_order_3.Insert(25);
  empty_tree_order_3.Insert(75);
  empty_tree_order_3.Insert(30);
  empty_tree_order_3.Insert(40);
  auto actual = empty_tree_order_3.ToString();
  std::string expected = "(25)(30, 50)(40)(75)";
  EXPECT_EQ(actual, expected);
}

TEST_F(BTreeTest, AfterThreeSplit_ToString_ReturnsExpectedString) {
  empty_tree_order_3.Insert(50);
  empty_tree_order_3.Insert(25);
  empty_tree_order_3.Insert(75);
  empty_tree_order_3.Insert(30);
  empty_tree_order_3.Insert(40);
  empty_tree_order_3.Insert(90);
  empty_tree_order_3.Insert(80);
  auto actual = empty_tree_order_3.ToString();
  std::string expected = "(25)(30)(40)(50)(75)(80)(90)";
  EXPECT_EQ(actual, expected);
}

TEST_F(BTreeTest, BTreeExample_ToString_ReturnsExpectedString) {
  empty_tree_order_5.Insert(1);
  empty_tree_order_5.Insert(2);
  empty_tree_order_5.Insert(5);
  empty_tree_order_5.Insert(6);
  empty_tree_order_5.Insert(7);
  empty_tree_order_5.Insert(9);
  empty_tree_order_5.Insert(12);
  empty_tree_order_5.Insert(16);
  empty_tree_order_5.Insert(18);
  empty_tree_order_5.Insert(21);

  auto actual = empty_tree_order_5.ToString();
  std::string expected = "(1, 2)(5, 9)(6, 7)(12, 16, 18, 21)";
  EXPECT_EQ(actual, expected);
}

TEST_F(BTreeTest, BTreeExample2_ToString_ReturnsExpectedString) {
  for (int i = 1; i <= 7; i++)
    empty_tree_order_3.Insert(i);

  auto actual = empty_tree_order_3.ToString();
  std::string expected = "(1)(2)(3)(4)(5)(6)(7)";
  EXPECT_EQ(actual, expected);
}

TEST_F(BTreeTest, BTreeExample3_ToString_ReturnsExpectedString) {
  for (int i = 1; i <= 8; i++) {
    empty_tree_order_3.Insert(i);
  }

  auto actual = empty_tree_order_3.ToString();
  std::string expected = "(1)(2)(3)(4)(5)(6)(7, 8)";
  EXPECT_EQ(actual, expected);
}

TEST_F(BTreeTest, BTreeExample4_ToString_ReturnsExpectedString) {
  for (int i = 1; i <= 31; i++) {
    empty_tree_order_3.Insert(i);
  }

  auto actual = empty_tree_order_3.ToString();
  std::string expected =
      "(1)(2)(3)(4)(5)(6)(7)(8)(9)(10)(11)(12)(13)(14)(15)(16)(17)(18)(19)(20)("
      "21)(22)(23)(24)(25)(26)(27)(28)(29)(30)(31)";
  EXPECT_EQ(actual, expected);
}

TEST_F(BTreeTest, BTreeExample5_ToString_ReturnsExpectedString) {
  for (int i = 31; i >= 1; i--) {
    empty_tree_order_3.Insert(i);
  }

  auto actual = empty_tree_order_3.ToString();
  std::string expected =
      "(1)(2)(3)(4)(5)(6)(7)(8)(9)(10)(11)(12)(13)(14)(15)(16)(17)(18)(19)(20)("
      "21)(22)(23)(24)(25)(26)(27)(28)(29)(30)(31)";
  EXPECT_EQ(actual, expected);
}

TEST_F(BTreeTest, BTreeExample6_ToString_ReturnsExpectedString) {
  for (int i = 17; i >= 1; i--)
    empty_tree_order_5.Insert(i);

  auto actual = empty_tree_order_5.ToString();
  std::string expected =
      "(1, 2)(3, 6)(4, 5)(7, 8)(9)(10, 11)(12, 15)(13, 14)(16, 17)";
  EXPECT_EQ(actual, expected);
}

TEST_F(BTreeTest, BTreeExample7_ToString_ReturnsExpectedString) {
  for (int i = 1; i <= 35; i++)
    empty_tree_order_5.Insert(i);

  auto actual = empty_tree_order_5.ToString();
  std::string expected =
      "(10, 11)(12, 15)(13, 14)(16, 17)(1, 2)(3, 6)(4, 5)(7, 8)(9, 18, 27)(19, "
      "20)(21, 24)(22, 23)(25, 26)(28, 29)(30, 33)(31, 32)(34, 35)";
  EXPECT_EQ(actual, expected);
}

TEST_F(BTreeTest, BTreeExample8_ToString_ReturnsExpectedString) {
  for (int i = 1; i <= 32; i++)
    empty_tree_order_4.Insert(i);

  auto actual = empty_tree_order_4.ToString();
  std::string expected =
      "(1)(2)(3)(4)(5)(6)(7)(8, 16)(9)(10)(11)(12)(13)(14)(15)(17)(18)(19)(20, "
      "24)(21)(22)(23)(27)(25)(26, 28, 30)(29)(31, 32)";
  EXPECT_EQ(actual, expected);
}

TEST_F(BTreeTest, AfterInserting1000Elements_Count_Returns1000) {
  for (int i = 1; i <= 1000; i++)
    empty_tree_order_3.Insert(i);

  auto actual = empty_tree_order_3.Size();
  uint16_t expected = 1000;
  EXPECT_EQ(actual, expected);
}

TEST_F(BTreeTest, AfterInserting500Elements_Count_Returns500) {
  for (int i = 1; i <= 500; i++)
    empty_tree_order_4.Insert(i);

  auto actual = empty_tree_order_4.Size();
  uint16_t expected = 500;
  EXPECT_EQ(actual, expected);
}

TEST_F(BTreeTest, AfterInserting100Elements_Count_Returns100) {
  for (int i = 1; i <= 100; i++)
    empty_tree_order_5.Insert(i);

  auto actual = empty_tree_order_5.Size();
  uint16_t expected = 100;
  EXPECT_EQ(actual, expected);
}

TEST_F(BTreeTest,
       AfterInsertingMultipleElements_GetHeight_ReturnsExpectedValue) {
  for (int i = 1; i <= 7; i++)
    empty_tree_order_3.Insert(i);

  auto actual = empty_tree_order_3.GetHeight();
  uint16_t expected = 3;
  EXPECT_EQ(actual, expected);
}

TEST_F(BTreeTest,
       AfterInsertingMultipleElements_GetHeight_ReturnsExpectedValue2) {
  for (int i = 31; i >= 1; i--) {
    empty_tree_order_3.Insert(i);
  }

  auto actual = empty_tree_order_3.GetHeight();
  uint16_t expected = 5;
  EXPECT_EQ(actual, expected);
}

#ifdef BTREE_BENCHMARK
TEST_F(BTreeTest,
       AfterInsertingMultipleElements_GetSplitCounter_ReturnsExpectedValue) {
  for (int i = 1; i <= 7; i++)
    empty_tree_order_3.Insert(i);

  auto actual = empty_tree_order_3.GetSplitCount();
  uint32_t expected = 4;
  EXPECT_EQ(actual, expected);
}

TEST_F(BTreeTest,
       AfterInsertingMultipleElements_GetSplitCounter_ReturnsExpectedValue2) {
  for (int i = 31; i >= 1; i--) {
    empty_tree_order_3.Insert(i);
  }

  auto actual = empty_tree_order_3.GetSplitCount();
  uint16_t expected = 26;
  EXPECT_EQ(actual, expected);
}
#endif
}  // namespace tree_test