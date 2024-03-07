#include "disjoint_set_test.h"
#include "disjoint_set.h"

namespace disjoint_set_test {
TEST_F(DisjointSetTest, AfterInstantiation_Expect_ValueEqualToIndex) {
  EXPECT_EQ(disjoint_set_.FindBlock(10), 10);
}

TEST_F(DisjointSetTest, FindBiggerThanSize_Expect_OutOfRangeException) {
  EXPECT_THROW(disjoint_set_.FindBlock(size_ + 1), std::out_of_range);
}

TEST_F(DisjointSetTest, AfterMerge_Expect_CorrectValue) {
  uint16_t first_block = 1, second_block = 2;

  disjoint_set_.MergeBlocks(first_block, second_block);
  EXPECT_EQ(disjoint_set_.FindBlock(second_block), first_block);
}

TEST_F(DisjointSetTest, AfterSeveralMerges_Expect_CorrectValue) {
  uint16_t first_block = 1, second_block = 2, third_block = 3;

  disjoint_set_.MergeBlocks(second_block, third_block);
  disjoint_set_.MergeBlocks(first_block, second_block);
  EXPECT_EQ(disjoint_set_.FindBlock(third_block), first_block);
}
}  // namespace disjoint_set_test