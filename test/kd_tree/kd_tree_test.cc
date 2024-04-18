#include "kd_tree_test.h"

namespace kd_tree_test {
std::vector<uint16_t> mo1 = {1, 2, 3};
std::vector<uint16_t> mo2 = {2, 3, 1};
std::vector<uint16_t> mo3 = {1, 3, 1};
std::vector<uint16_t> mo4 = {1, 3, 2};

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

TEST_F(KdTreeTest, PartialMatch_ReturnsAllTheThree_IfTheMaskIsSetToAllZeros) {
  kd_tree_.Insert(mo1);
  kd_tree_.Insert(mo2);
  kd_tree_.Insert(mo3);

  std::set<std::vector<uint16_t>> expected_result;
  expected_result.insert(mo1);
  expected_result.insert(mo2);
  expected_result.insert(mo3);

  std::vector<bool> mask(3, false);
  auto actual_result = kd_tree_.PartialMatch(mo1, mask);

  EXPECT_EQ(expected_result, actual_result);
}

TEST_F(KdTreeTest, PartialMatch_ReturnsCorrectSet_IfMaskHasOneOne) {
  kd_tree_.Insert(mo1);
  kd_tree_.Insert(mo2);
  kd_tree_.Insert(mo3);

  std::set<std::vector<uint16_t>> expected_result;
  expected_result.insert(mo2);
  expected_result.insert(mo3);

  std::vector<bool> mask = {false, true, false};
  auto actual_result = kd_tree_.PartialMatch(mo2, mask);

  EXPECT_EQ(expected_result, actual_result);
}

TEST_F(KdTreeTest, PartialMatch_ReturnsCorrectSet_DeeperThanSecondLevel) {
  kd_tree_.Insert(mo1);
  kd_tree_.Insert(mo2);
  kd_tree_.Insert(mo3);
  kd_tree_.Insert(mo4);

  std::set<std::vector<uint16_t>> expected_result;
  expected_result.insert(mo2);
  expected_result.insert(mo3);
  expected_result.insert(mo4);

  std::vector<bool> mask = {false, true, false};
  auto actual_result = kd_tree_.PartialMatch(mo2, mask);

  EXPECT_EQ(expected_result, actual_result);
}
}  // namespace kd_tree_test