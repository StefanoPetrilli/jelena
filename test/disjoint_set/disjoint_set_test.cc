#include "disjoint_set_test.h"
#include "block_identifier.h"
#include "disjoint_set.h"
#include "rank_quick_union_test.h"
#include "weighted_quick_union_test.h"

namespace disjoint_set_test {
TEST_F(QuickUnionTest, AfterInstantiation_Expect_ValueEqualToIndex) {
  EXPECT_EQ(quick_union_set_.FindBlock(10), 10);
}

TEST_F(QuickUnionTest, FindBiggerThanSize_Expect_OutOfRangeException) {
  EXPECT_THROW(quick_union_set_.FindBlock(size_ + 1), std::out_of_range);
}

TEST_F(QuickUnionTest, AfterMerge_Expect_CorrectValue) {
  quick_union_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                               BlockIdentifier::kSecondBlock);
  EXPECT_EQ(quick_union_set_.FindBlock(BlockIdentifier::kSecondBlock),
            BlockIdentifier::kFirstBlock);
}

TEST_F(QuickUnionTest, AfterSeveralMerges_Expect_CorrectValue) {
  quick_union_set_.MergeBlocks(BlockIdentifier::kSecondBlock,
                               BlockIdentifier::kThirdBlock);
  quick_union_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                               BlockIdentifier::kSecondBlock);
  EXPECT_EQ(quick_union_set_.FindBlock(BlockIdentifier::kThirdBlock),
            BlockIdentifier::kFirstBlock);
}

TEST_F(WeightedQuickUnion, AfterInstantiation_Expect_ValueEqualToIndex) {
  EXPECT_EQ(weighted_disjoint_set_.FindBlock(10), 10);
}

TEST_F(WeightedQuickUnion, FindBiggerThanSize_Expect_OutOfRangeException) {
  EXPECT_THROW(weighted_disjoint_set_.FindBlock(size_ + 1), std::out_of_range);
}

TEST_F(WeightedQuickUnion,
       AfterMergeOfEqualWeight_Expect_FirstBlockGoesIntoSecondBlock) {
  weighted_disjoint_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                     BlockIdentifier::kSecondBlock);
  auto result = weighted_disjoint_set_.FindBlock(BlockIdentifier::kSecondBlock);
  EXPECT_EQ(result, BlockIdentifier::kFirstBlock);
}

TEST_F(WeightedQuickUnion,
       AfterMergeOfUnequalWeight_Expect_SmallerBecomesChildOfBigger) {
  weighted_disjoint_set_.MergeBlocks(BlockIdentifier::kSecondBlock,
                                     BlockIdentifier::kThirdBlock);
  weighted_disjoint_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                     BlockIdentifier::kSecondBlock);

  EXPECT_EQ(weighted_disjoint_set_.FindBlock(BlockIdentifier::kFirstBlock),
            BlockIdentifier::kSecondBlock);
}

TEST_F(WeightedQuickUnion,
       AfterMergeOfUnequalWeight_Expect_SmallerBecomesChildOfBigger2) {
  //Create the first subtree
  weighted_disjoint_set_.MergeBlocks(BlockIdentifier::kSecondBlock,
                                     BlockIdentifier::kThirdBlock);
  weighted_disjoint_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                     BlockIdentifier::kThirdBlock);

  //Create the second subtree
  weighted_disjoint_set_.MergeBlocks(BlockIdentifier::kFourthBlock,
                                     BlockIdentifier::kFifthBlock);
  weighted_disjoint_set_.MergeBlocks(BlockIdentifier::kFourthBlock,
                                     BlockIdentifier::kSixthBlock);

  //Merge the two subtrees
  weighted_disjoint_set_.MergeBlocks(BlockIdentifier::kSecondBlock,
                                     BlockIdentifier::kFourthBlock);

  EXPECT_EQ(weighted_disjoint_set_.FindBlock(BlockIdentifier::kSixthBlock),
            BlockIdentifier::kSecondBlock);
}

TEST_F(WeightedQuickUnion,
       AfterMergeOfUnequalWeight_Expect_SmallerBecomesChildOfBigger3) {
  //Create the first subtree
  weighted_disjoint_set_.MergeBlocks(BlockIdentifier::kSecondBlock,
                                     BlockIdentifier::kThirdBlock);
  weighted_disjoint_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                     BlockIdentifier::kThirdBlock);

  //Create the second subtree
  weighted_disjoint_set_.MergeBlocks(BlockIdentifier::kFourthBlock,
                                     BlockIdentifier::kFifthBlock);
  weighted_disjoint_set_.MergeBlocks(BlockIdentifier::kFourthBlock,
                                     BlockIdentifier::kSixthBlock);

  //Merge the two subtrees
  weighted_disjoint_set_.MergeBlocks(BlockIdentifier::kFourthBlock,
                                     BlockIdentifier::kSecondBlock);

  EXPECT_EQ(weighted_disjoint_set_.FindBlock(BlockIdentifier::kSixthBlock),
            BlockIdentifier::kFourthBlock);
}

TEST_F(WeightedQuickUnion,
       AfterMultipleMergeOfUnequalWeight_Expect_SmallerBecomesChildOfBigger4) {
  //Create the first subtree
  weighted_disjoint_set_.MergeBlocks(BlockIdentifier::kSecondBlock,
                                     BlockIdentifier::kThirdBlock);
  weighted_disjoint_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                     BlockIdentifier::kThirdBlock);

  //Create the second subtree
  weighted_disjoint_set_.MergeBlocks(BlockIdentifier::kFourthBlock,
                                     BlockIdentifier::kFifthBlock);
  weighted_disjoint_set_.MergeBlocks(BlockIdentifier::kFourthBlock,
                                     BlockIdentifier::kSixthBlock);
  weighted_disjoint_set_.MergeBlocks(BlockIdentifier::kFourthBlock,
                                     BlockIdentifier::kSeventhBlock);

  //Merge the two subtrees
  weighted_disjoint_set_.MergeBlocks(BlockIdentifier::kSecondBlock,
                                     BlockIdentifier::kFourthBlock);

  EXPECT_EQ(weighted_disjoint_set_.FindBlock(BlockIdentifier::kSixthBlock),
            BlockIdentifier::kFourthBlock);
}

TEST_F(WeightedQuickUnion,
       AfterMultipleMergeOfUnequalWeight_Expect_SmallerBecomesChildOfBigger5) {
  //Create the first subtree
  weighted_disjoint_set_.MergeBlocks(BlockIdentifier::kSecondBlock,
                                     BlockIdentifier::kThirdBlock);
  weighted_disjoint_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                     BlockIdentifier::kThirdBlock);

  //Create the second subtree
  weighted_disjoint_set_.MergeBlocks(BlockIdentifier::kFourthBlock,
                                     BlockIdentifier::kFifthBlock);
  weighted_disjoint_set_.MergeBlocks(BlockIdentifier::kFourthBlock,
                                     BlockIdentifier::kSixthBlock);
  weighted_disjoint_set_.MergeBlocks(BlockIdentifier::kFourthBlock,
                                     BlockIdentifier::kSeventhBlock);

  //Merge the two subtrees
  weighted_disjoint_set_.MergeBlocks(BlockIdentifier::kFourthBlock,
                                     BlockIdentifier::kSecondBlock);

  EXPECT_EQ(weighted_disjoint_set_.FindBlock(BlockIdentifier::kSixthBlock),
            BlockIdentifier::kFourthBlock);
}

TEST_F(RankQuickUnionTest, AfterInstantiation_Expect_ValueEqualToIndex) {
  EXPECT_EQ(rank_disjoint_set_.FindBlock(10), 10);
}

TEST_F(RankQuickUnionTest, FindBiggerThanSize_Expect_OutOfRangeException) {
  EXPECT_THROW(rank_disjoint_set_.FindBlock(size_ + 1), std::out_of_range);
}

TEST_F(RankQuickUnionTest,
       AfterMergeOfEqualRank_Expect_FirstBlockGoesIntoSecondBlock) {
  rank_disjoint_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                 BlockIdentifier::kSecondBlock);
  auto result = rank_disjoint_set_.FindBlock(BlockIdentifier::kSecondBlock);
  EXPECT_EQ(result, BlockIdentifier::kFirstBlock);
}

TEST_F(RankQuickUnionTest,
       AfterMergeOfUnequalRank_Expect_SmallerBecomesChildOfBigger1) {
  rank_disjoint_set_.MergeBlocks(BlockIdentifier::kSecondBlock,
                                 BlockIdentifier::kThirdBlock);
  rank_disjoint_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                 BlockIdentifier::kSecondBlock);

  EXPECT_EQ(rank_disjoint_set_.FindBlock(BlockIdentifier::kFirstBlock),
            BlockIdentifier::kSecondBlock);
}

TEST_F(RankQuickUnionTest,
       AfterMergeOfUnequalRank_Expect_SmallerBecomesChildOfBigger2) {
  //Create the first subtree
  rank_disjoint_set_.MergeBlocks(BlockIdentifier::kSecondBlock,
                                 BlockIdentifier::kThirdBlock);
  rank_disjoint_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                 BlockIdentifier::kThirdBlock);

  //Create the second subtree
  rank_disjoint_set_.MergeBlocks(BlockIdentifier::kFourthBlock,
                                 BlockIdentifier::kFifthBlock);
  rank_disjoint_set_.MergeBlocks(BlockIdentifier::kFourthBlock,
                                 BlockIdentifier::kSixthBlock);

  //Merge the two subtrees
  rank_disjoint_set_.MergeBlocks(BlockIdentifier::kSecondBlock,
                                 BlockIdentifier::kFourthBlock);

  EXPECT_EQ(rank_disjoint_set_.FindBlock(BlockIdentifier::kSixthBlock),
            BlockIdentifier::kSecondBlock);
}

TEST_F(RankQuickUnionTest,
       AfterMergeOfUnequalRank_Expect_SmallerBecomesChildOfBigger3) {
  //Create the first subtree
  rank_disjoint_set_.MergeBlocks(BlockIdentifier::kSecondBlock,
                                 BlockIdentifier::kThirdBlock);
  rank_disjoint_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                 BlockIdentifier::kThirdBlock);

  //Create the second subtree
  rank_disjoint_set_.MergeBlocks(BlockIdentifier::kFourthBlock,
                                 BlockIdentifier::kFifthBlock);
  rank_disjoint_set_.MergeBlocks(BlockIdentifier::kFourthBlock,
                                 BlockIdentifier::kSixthBlock);
  rank_disjoint_set_.MergeBlocks(BlockIdentifier::kFourthBlock,
                                 BlockIdentifier::kSeventhBlock);

  //Merge the two subtrees
  rank_disjoint_set_.MergeBlocks(BlockIdentifier::kSecondBlock,
                                 BlockIdentifier::kFourthBlock);

  EXPECT_EQ(rank_disjoint_set_.FindBlock(BlockIdentifier::kSixthBlock),
            BlockIdentifier::kSecondBlock);
}
}  // namespace disjoint_set_test