#include "linked_list.h"
#include "linked_list_test.h"

namespace linked_list_test {
TEST_F(LinkedListTest, BeforeInserting_ToString_ReturnsEmptyString) {
  EXPECT_EQ(_linked_list.ToString(), std::string());
}

TEST_F(LinkedListTest, BeforeInserting_Size_Returns0) {
  EXPECT_EQ(_linked_list.Size(), 0);
}

TEST_F(LinkedListTest, AfterInserting_ToString_ReturnsExpectedValue) {
  _linked_list.Insert(10);

  EXPECT_EQ(_linked_list.ToString(), "10");
}

TEST_F(LinkedListTest, AfterMultipleInserting_ToString_ReturnsExpectedValue) {
  _linked_list.Insert(10);
  _linked_list.Insert(10);

  EXPECT_EQ(_linked_list.ToString(), "10 10");
}

TEST_F(LinkedListTest, BeforeInserting_IsEmpty_ReturnsTrue) {
  EXPECT_TRUE(_linked_list.IsEmpty());
}

TEST_F(LinkedListTest, AfterInserting_IsEmpty_ReturnsFalse) {
  _linked_list.Insert(10);

  EXPECT_FALSE(_linked_list.IsEmpty());
}

TEST_F(LinkedListTest, BeforeInserting_Get_ReturnsAnException) {
  ASSERT_THROW(_linked_list[0], std::out_of_range);
}

TEST_F(LinkedListTest, AfterInserting_Get_ReturnsAnException) {
  _linked_list.Insert(10);
  _linked_list.Insert(10);
  _linked_list.Insert(10);

  ASSERT_THROW(_linked_list[99], std::out_of_range);
}

TEST_F(LinkedListTest, AfterInserting_Get_ReturnsExpectedValue) {
  _linked_list.Insert(10);
  _linked_list.Insert(20);

  EXPECT_EQ(_linked_list[1], 20);
}

TEST_F(LinkedListTest, AfterInserting_Size_ReturnsExpectedValue) {
  _linked_list.Insert(10);
  _linked_list.Insert(20);
  _linked_list.Insert(30);
  _linked_list.Insert(40);

  EXPECT_EQ(_linked_list.Size(), 4);
}
}  // namespace linked_list_test