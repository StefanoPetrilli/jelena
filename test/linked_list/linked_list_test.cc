#include "linked_list.h"
#include "linked_list_test.h"

namespace linked_list_test {
TEST_F(LinkedListTest, BeforeInserting_ToString_ReturnsEmptyString) {
  EXPECT_EQ(linked_list_.ToString(), std::string());
}

TEST_F(LinkedListTest, BeforeInserting_Size_Returns0) {
  EXPECT_EQ(linked_list_.Size(), 0);
}

TEST_F(LinkedListTest, AfterInserting_ToString_ReturnsExpectedValue) {
  linked_list_.Insert(10);

  EXPECT_EQ(linked_list_.ToString(), "10");
}

TEST_F(LinkedListTest, AfterMultipleInserting_ToString_ReturnsExpectedValue) {
  linked_list_.Insert(10);
  linked_list_.Insert(10);

  EXPECT_EQ(linked_list_.ToString(), "10 10");
}

TEST_F(LinkedListTest, BeforeInserting_IsEmpty_ReturnsTrue) {
  EXPECT_TRUE(linked_list_.IsEmpty());
}

TEST_F(LinkedListTest, AfterInserting_IsEmpty_ReturnsFalse) {
  linked_list_.Insert(10);

  EXPECT_FALSE(linked_list_.IsEmpty());
}

TEST_F(LinkedListTest, BeforeInserting_Get_ReturnsAnException) {
  ASSERT_THROW(linked_list_[0], std::out_of_range);
}

TEST_F(LinkedListTest, AfterInserting_Get_ReturnsAnException) {
  linked_list_.Insert(10);
  linked_list_.Insert(10);
  linked_list_.Insert(10);

  ASSERT_THROW(linked_list_[99], std::out_of_range);
}

TEST_F(LinkedListTest, AfterInserting_Get_ReturnsExpectedValue) {
  linked_list_.Insert(10);
  linked_list_.Insert(20);

  EXPECT_EQ(linked_list_[1], 20);
}

TEST_F(LinkedListTest, AfterInsertingAndDeleting_Get_ReturnsExpectedValue) {
  linked_list_.Insert(10);
  linked_list_.Insert(15);
  linked_list_.Insert(20);
  linked_list_.Delete(1);

  EXPECT_EQ(linked_list_[1], 20);
}

TEST_F(LinkedListTest, AfterInserting_Size_ReturnsExpectedValue) {
  linked_list_.Insert(10);
  linked_list_.Insert(20);
  linked_list_.Insert(30);
  linked_list_.Insert(40);

  EXPECT_EQ(linked_list_.Size(), 4);
}

TEST_F(LinkedListTest, AfterInsertingAndDeleting_Size_ReturnsExpectedValue) {
  linked_list_.Insert(10);
  linked_list_.Insert(20);
  linked_list_.Insert(30);
  linked_list_.Delete(1);

  EXPECT_EQ(linked_list_.Size(), 2);
}

TEST_F(LinkedListTest, DeletingTail_Index_ReturnsTheCorrectElement) {
  linked_list_.Insert(10);
  linked_list_.Insert(20);
  linked_list_.Insert(30);
  linked_list_.Delete(2);

  EXPECT_EQ(linked_list_[1], 20);
}

TEST_F(LinkedListTest, DeleteAllTheElements_Empty_ReturnsTrue) {
  linked_list_.Insert(10);
  linked_list_.Delete(0);

  EXPECT_TRUE(linked_list_.IsEmpty());
}

TEST_F(LinkedListTest, Delete_OutOfRange_ReturnsAnException) {
  ASSERT_THROW(linked_list_.Delete(42), std::out_of_range);
}
}  // namespace linked_list_test