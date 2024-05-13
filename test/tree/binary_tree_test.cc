#include "binary_tree_test.h"

namespace tree_test {
TEST_F(BinaryTreeTest, EmptyTree_IsEmpty_ReturnsTrue) {
  EXPECT_TRUE(empty_tree.IsEmpty());
}

TEST_F(BinaryTreeTest, EmptyTreeAfterInsert_IsEmpty_ReturnsFalse) {
  empty_tree.Insert(0);
  EXPECT_FALSE(empty_tree.IsEmpty());
}

TEST_F(BinaryTreeTest, EmptyTree_Delete_ReturnsFalse) {
  EXPECT_FALSE(empty_tree.Remove(0));
}

TEST_F(BinaryTreeTest, TreeWithHead_Remove_ReturnsTrue) {
  empty_tree.Insert(0);
  EXPECT_TRUE(empty_tree.Remove(0));
}

TEST_F(BinaryTreeTest, EmptyTree_Search_ReturnsNullptr) {
  EXPECT_EQ(empty_tree.Search(0), nullptr);
}

TEST_F(BinaryTreeTest, HeadOnlyTree_Search_ReturnsNode) {
  int value = 0;
  empty_tree.Insert(value);
  auto node = empty_tree.Search(value);
  if (node == nullptr)
    FAIL();
  EXPECT_EQ(node->GetValue(), value);
}

TEST_F(BinaryTreeTest, HeadOnlyTreeAfterDelete_IsEmpty_ReturnsTrue) {
  empty_tree.Insert(0);
  empty_tree.Remove(0);
  EXPECT_TRUE(empty_tree.IsEmpty());
}

TEST_F(BinaryTreeTest,
       EmptyTreeMultipleInsertion_Search_ReturnsExpectedStructure) {
  int head_value = 0;
  int right_child_value = 10;

  empty_tree.Insert(head_value);
  empty_tree.Insert(right_child_value);

  auto head = empty_tree.Search(head_value);
  EXPECT_EQ(head->GetNextNode()->GetValue(), right_child_value);
}

}  // namespace tree_test