#include "b_tree_test.h"

namespace tree_test {

TEST_F(BTreeTest, EmptyTree_GetOrder_ReturnsOrder) {
  EXPECT_EQ(empty_tree.GetOrder(), 5);
}

TEST_F(BTreeTest, EmptyTree_IsEmpty_ReturnsTrue) {
  EXPECT_TRUE(empty_tree.IsEmpty());
}

TEST_F(BTreeTest, EmptyTreeAfterInsert_IsEmpty_ReturnsFalse) {
  empty_tree.Insert(0);
  EXPECT_FALSE(empty_tree.IsEmpty());
}

TEST_F(BTreeTest, EmptyTree_ToString_ReturnsExpectedString) {
  auto actual = empty_tree.ToString();
  std::string expected = "[Values: ()]";

  EXPECT_EQ(actual, expected);
}

TEST_F(BTreeTest, EmptyTreeInsertFirstNode_ToString_ReturnsExpectedString) {
  empty_tree.Insert(0);
  empty_tree.Insert(1);
  empty_tree.Insert(2);
  empty_tree.Insert(3);
  auto actual = empty_tree.ToString();
  std::string expected = "[Values: (0, 1, 2, 3)]";

  EXPECT_EQ(actual, expected);
}

TEST_F(BTreeTest, AfterSplit_ToString_ReturnsExpectedString) {
  empty_tree.Insert(0);
  empty_tree.Insert(1);
  empty_tree.Insert(2);
  empty_tree.Insert(3);
  empty_tree.Insert(4);
  auto actual = empty_tree.ToString();
  std::string expected = "[Values: (0, 1)][Values: (2)][Values: (3, 4)]";

  EXPECT_EQ(actual, expected);
}

// TEST_F(BTreeTest, EmptyTree_Delete_ReturnsFalse) {
//   EXPECT_FALSE(empty_tree.Remove(0));
// }

// TEST_F(BTreeTest, TreeWithHead_Remove_ReturnsTrue) {
//   empty_tree.Insert(0);
//   EXPECT_TRUE(empty_tree.Remove(0));
// }

// TEST_F(BTreeTest, EmptyTree_Search_ReturnsNullptr) {
//   EXPECT_EQ(empty_tree.Search(0), nullptr);
// }

// TEST_F(BTreeTest, HeadOnlyTree_Search_ReturnsNode) {
//   int value = 0;
//   empty_tree.Insert(value);
//   auto node = empty_tree.Search(value);
//   if (node == nullptr)
//     FAIL();
//   EXPECT_EQ(node->GetValue(), value);
// }

// TEST_F(BTreeTest, HeadOnlyTreeAfterDelete_IsEmpty_ReturnsTrue) {
//   empty_tree.Insert(0);
//   empty_tree.Remove(0);
//   EXPECT_TRUE(empty_tree.IsEmpty());
// }

// TEST_F(BTreeTest,
//        EmptyTreeMultipleInsertion_Search_ReturnsExpectedStructure) {
//   int head_value = 0;
//   int right_child_value = 10;

//   empty_tree.Insert(head_value);
//   empty_tree.Insert(right_child_value);

//   auto head = empty_tree.Search(head_value);
//   EXPECT_EQ(head->GetNextNode()->GetValue(), right_child_value);
// }

}  // namespace tree_test