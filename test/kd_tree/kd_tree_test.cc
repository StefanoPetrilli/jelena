#include "kd_tree_test.h"

namespace kd_tree_test {
std::vector<uint16_t> mo1 = {1, 2, 3};
std::vector<uint16_t> mo2 = {2, 3, 1};
std::vector<uint16_t> mo3 = {1, 3, 1};

TEST_F(KdTreeTest, BeforeInserting_ToString_ReturnsEmptyString) {
  EXPECT_EQ(kd_tree_.ToString(), std::string());
}

TEST_F(KdTreeTest, ToString_ReturnsCorrectString_AfterInsertingOneElement) {
  kd_tree_.Insert(mo1);
  EXPECT_EQ(kd_tree_.ToString(), "(1 2 3)");
}

TEST_F(KdTreeTest,
       ToString_ReturnsCorrectString_AfterInsertingTwoElementsInOrder) {
  kd_tree_.Insert(mo1);
  kd_tree_.Insert(mo2);
  EXPECT_EQ(kd_tree_.ToString(), "(2 3 1)(1 2 3)");
}

TEST_F(KdTreeTest,
       ToString_ReturnsCorrectString_AfterInsertingTwoElementsInReverseOrder) {
  kd_tree_.Insert(mo2);
  kd_tree_.Insert(mo1);
  EXPECT_EQ(kd_tree_.ToString(), "(2 3 1)(1 2 3)");
}

TEST_F(KdTreeTest, ToString_ReturnsCorrectString_AfterInsertingThreeElements) {
  kd_tree_.Insert(mo1);
  kd_tree_.Insert(mo2);
  kd_tree_.Insert(mo3);

  EXPECT_EQ(kd_tree_.ToString(), "(2 3 1)(1 2 3)(1 3 1)");
}

TEST_F(KdTreeTest, ToString_ReturnsCorrectString_AfterFiveDepthInsertion) {
  kd_tree_.Insert(mo1);
  kd_tree_.Insert(mo1);
  kd_tree_.Insert(mo1);
  kd_tree_.Insert(mo1);
  kd_tree_.Insert(mo1);

  EXPECT_EQ(kd_tree_.ToString(), "(1 2 3)(1 2 3)(1 2 3)(1 2 3)(1 2 3)");
}
}  // namespace kd_tree_test