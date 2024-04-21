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
  std::string expected = "[Values: ()]";

  EXPECT_EQ(actual, expected);
}

TEST_F(BTreeTest, EmptyTreeInsertFirstNode_ToString_ReturnsExpectedString) {
  empty_tree_order_5.Insert(0);
  empty_tree_order_5.Insert(1);
  empty_tree_order_5.Insert(2);
  empty_tree_order_5.Insert(3);
  auto actual = empty_tree_order_5.ToString();
  std::string expected = "[Values: (0, 1, 2, 3)]";

  EXPECT_EQ(actual, expected);
}

TEST_F(BTreeTest, AfterSplit_ToString_ReturnsExpectedString) {
  empty_tree_order_3.Insert(50);
  empty_tree_order_3.Insert(25);
  empty_tree_order_3.Insert(75);
  auto actual = empty_tree_order_3.ToString();
  std::string expected = "[Values: (25)][Values: (50)][Values: (75)]";
  EXPECT_EQ(actual, expected);
}

TEST_F(BTreeTest, AfterMultipleSplit_ToString_ReturnsExpectedString) {
  empty_tree_order_3.Insert(50);
  empty_tree_order_3.Insert(25);
  empty_tree_order_3.Insert(75);
  empty_tree_order_3.Insert(30);
  empty_tree_order_3.Insert(40);
  auto actual = empty_tree_order_3.ToString();
  std::string expected = "[Values: (25)][Values: (30, 50)][Values: (40)][Values: (75)]";
  EXPECT_EQ(actual, expected);
}
}  // namespace tree_test