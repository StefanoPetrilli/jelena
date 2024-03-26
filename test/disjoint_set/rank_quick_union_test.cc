#include "rank_quick_union_test.h"
#include "block_identifier.h"

namespace disjoint_set_test {
TEST_F(RankQuickUnionTest, AfterInstantiation_Expect_ValueEqualToIndex) {
  EXPECT_EQ(rank_disjoint_set_.FindBlock(kFifthBlock), kFifthBlock);
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

TEST_F(RankQuickUnionTest,
       AfterInstantiation_Expect_CorrectNumberOfDistinctBlocks) {
  EXPECT_EQ(rank_disjoint_set_.GetDistinctBlocks(), size_);
}

TEST_F(RankQuickUnionTest, AfterMerge_Expect_CorrectDistinctBlocksValue) {
  rank_disjoint_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                 BlockIdentifier::kSecondBlock);
  EXPECT_EQ(rank_disjoint_set_.GetDistinctBlocks(), size_ - 1);
}

TEST_F(RankQuickUnionTest,
       AfterMergeOfSameBlock_Expect_CorrectDistinctBlocksValue) {
  rank_disjoint_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                 BlockIdentifier::kSecondBlock);
  rank_disjoint_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                 BlockIdentifier::kSecondBlock);
  EXPECT_EQ(rank_disjoint_set_.GetDistinctBlocks(), size_ - 1);
}

TEST_F(RankQuickUnionTest,
       AfterSeveralMerges_Expect_CorrectDistinctBlocksValue) {
  rank_disjoint_set_.MergeBlocks(BlockIdentifier::kSecondBlock,
                                 BlockIdentifier::kThirdBlock);
  rank_disjoint_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                 BlockIdentifier::kSecondBlock);
  EXPECT_EQ(rank_disjoint_set_.GetDistinctBlocks(), size_ - 2);
}

TEST_F(RankQuickUnionTest,
       AfterSeveralMerges_Expect_CorrectDistinctBlocksValue_2) {
  rank_disjoint_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                 BlockIdentifier::kSecondBlock);
  rank_disjoint_set_.MergeBlocks(BlockIdentifier::kSecondBlock,
                                 BlockIdentifier::kThirdBlock);
  rank_disjoint_set_.MergeBlocks(BlockIdentifier::kThirdBlock,
                                 BlockIdentifier::kFourthBlock);
  EXPECT_EQ(rank_disjoint_set_.GetDistinctBlocks(), size_ - 3);
}

TEST_F(RankQuickUnionTest,
       UsingFullCompressionAfterInstantiation_Expect_ValueEqualToIndex) {
  EXPECT_EQ(rank_disjoint_set_.FindBlockFullCompression(kFifthBlock),
            kFifthBlock);
}

TEST_F(RankQuickUnionTest,
       UsingFullCompressionFindBiggerThanSize_Expect_OutOfRangeException) {
  EXPECT_THROW(rank_disjoint_set_.FindBlockFullCompression(size_ + 1),
               std::out_of_range);
}

TEST_F(
    RankQuickUnionTest,
    UsingFullCompressionAfterMergeOfEqualRank_Expect_FirstBlockGoesIntoSecondBlock) {
  rank_disjoint_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                 BlockIdentifier::kSecondBlock);
  auto result = rank_disjoint_set_.FindBlockFullCompression(
      BlockIdentifier::kSecondBlock);
  EXPECT_EQ(result, BlockIdentifier::kFirstBlock);
}

TEST_F(
    RankQuickUnionTest,
    UsingFullCompressionAfterMergeOfUnequalRank_Expect_SmallerBecomesChildOfBigger1) {
  rank_disjoint_set_.MergeBlocks(BlockIdentifier::kSecondBlock,
                                 BlockIdentifier::kThirdBlock);
  rank_disjoint_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                 BlockIdentifier::kSecondBlock);

  EXPECT_EQ(
      rank_disjoint_set_.FindBlockFullCompression(BlockIdentifier::kFirstBlock),
      BlockIdentifier::kSecondBlock);
}

TEST_F(
    RankQuickUnionTest,
    UsingFullCompressionAfterMergeOfUnequalRank_Expect_SmallerBecomesChildOfBigger2) {
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

  EXPECT_EQ(
      rank_disjoint_set_.FindBlockFullCompression(BlockIdentifier::kSixthBlock),
      BlockIdentifier::kSecondBlock);
}

TEST_F(
    RankQuickUnionTest,
    UsingFullCompressionAfterMergeOfUnequalRank_Expect_SmallerBecomesChildOfBigger3) {
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

  EXPECT_EQ(
      rank_disjoint_set_.FindBlockFullCompression(BlockIdentifier::kSixthBlock),
      BlockIdentifier::kSecondBlock);
}

TEST_F(RankQuickUnionTest,
       UsingPathHalvingAfterInstantiation_Expect_ValueEqualToIndex) {
  EXPECT_EQ(rank_disjoint_set_.FindBlockPathHalving(kFifthBlock), kFifthBlock);
}

TEST_F(RankQuickUnionTest,
       UsingPathHalvingFindBiggerThanSize_Expect_OutOfRangeException) {
  EXPECT_THROW(rank_disjoint_set_.FindBlockPathHalving(size_ + 1),
               std::out_of_range);
}

TEST_F(
    RankQuickUnionTest,
    UsingPathHalvingAfterMergeOfEqualRank_Expect_FirstBlockGoesIntoSecondBlock) {
  rank_disjoint_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                 BlockIdentifier::kSecondBlock);
  auto result =
      rank_disjoint_set_.FindBlockPathHalving(BlockIdentifier::kSecondBlock);
  EXPECT_EQ(result, BlockIdentifier::kFirstBlock);
}

TEST_F(
    RankQuickUnionTest,
    UsingPathHalvingAfterMergeOfUnequalRank_Expect_SmallerBecomesChildOfBigger1) {
  rank_disjoint_set_.MergeBlocks(BlockIdentifier::kSecondBlock,
                                 BlockIdentifier::kThirdBlock);
  rank_disjoint_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                 BlockIdentifier::kSecondBlock);

  EXPECT_EQ(
      rank_disjoint_set_.FindBlockPathHalving(BlockIdentifier::kFirstBlock),
      BlockIdentifier::kSecondBlock);
}

TEST_F(
    RankQuickUnionTest,
    UsingPathHalvingAfterMergeOfUnequalRank_Expect_SmallerBecomesChildOfBigger2) {
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

  EXPECT_EQ(
      rank_disjoint_set_.FindBlockPathHalving(BlockIdentifier::kSixthBlock),
      BlockIdentifier::kSecondBlock);
}

TEST_F(
    RankQuickUnionTest,
    UsingPathHalvingAfterMergeOfUnequalRank_Expect_SmallerBecomesChildOfBigger3) {
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

  EXPECT_EQ(
      rank_disjoint_set_.FindBlockPathHalving(BlockIdentifier::kSixthBlock),
      BlockIdentifier::kSecondBlock);
}

TEST_F(RankQuickUnionTest,
       UsingPathSplittingAfterInstantiation_Expect_ValueEqualToIndex) {
  EXPECT_EQ(rank_disjoint_set_.FindBlockPathSplitting(kFifthBlock),
            kFifthBlock);
}

TEST_F(RankQuickUnionTest,
       UsingPathSplittingFindBiggerThanSize_Expect_OutOfRangeException) {
  EXPECT_THROW(rank_disjoint_set_.FindBlockPathSplitting(size_ + 1),
               std::out_of_range);
}

TEST_F(
    RankQuickUnionTest,
    UsingPathSplittingAfterMergeOfEqualRank_Expect_FirstBlockGoesIntoSecondBlock) {
  rank_disjoint_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                 BlockIdentifier::kSecondBlock);
  auto result =
      rank_disjoint_set_.FindBlockPathSplitting(BlockIdentifier::kSecondBlock);
  EXPECT_EQ(result, BlockIdentifier::kFirstBlock);
}

TEST_F(
    RankQuickUnionTest,
    UsingPathSplittingAfterMergeOfUnequalRank_Expect_SmallerBecomesChildOfBigger1) {
  rank_disjoint_set_.MergeBlocks(BlockIdentifier::kSecondBlock,
                                 BlockIdentifier::kThirdBlock);
  rank_disjoint_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                 BlockIdentifier::kSecondBlock);

  EXPECT_EQ(
      rank_disjoint_set_.FindBlockPathSplitting(BlockIdentifier::kFirstBlock),
      BlockIdentifier::kSecondBlock);
}

TEST_F(
    RankQuickUnionTest,
    UsingPathSplittingAfterMergeOfUnequalRank_Expect_SmallerBecomesChildOfBigger2) {
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

  EXPECT_EQ(
      rank_disjoint_set_.FindBlockPathSplitting(BlockIdentifier::kSixthBlock),
      BlockIdentifier::kSecondBlock);
}

TEST_F(
    RankQuickUnionTest,
    UsingPathSplittingAfterMergeOfUnequalRank_Expect_SmallerBecomesChildOfBigger3) {
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

  EXPECT_EQ(
      rank_disjoint_set_.FindBlockPathSplitting(BlockIdentifier::kSixthBlock),
      BlockIdentifier::kSecondBlock);
}

#ifdef FULL_BENCHMARK
TEST_F(RankQuickUnionTest,
       AfterInstantiationGetTotalPathLenght_Expect_CorrectValue) {
  EXPECT_EQ(rank_disjoint_set_.GetTotalPathLenght(), 0);
}

TEST_F(RankQuickUnionTest,
       AfterComplexMergeGetTotalPathLenght_Expect_CorrectValue) {
  rank_disjoint_set_.MergeBlocks(BlockIdentifier::kThirdBlock,
                                 BlockIdentifier::kFourthBlock);
  rank_disjoint_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                 BlockIdentifier::kSecondBlock);
  rank_disjoint_set_.MergeBlocks(BlockIdentifier::kFourthBlock,
                                 BlockIdentifier::kFifthBlock);
  rank_disjoint_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                 BlockIdentifier::kNineBlock);
  rank_disjoint_set_.MergeBlocks(BlockIdentifier::kSecondBlock,
                                 BlockIdentifier::kTenthBlock);
  rank_disjoint_set_.MergeBlocks(BlockIdentifier::kEightBlock,
                                 BlockIdentifier::kSeventhBlock);
  EXPECT_EQ(rank_disjoint_set_.GetTotalPathLenght(), 6);
}
#endif

}  // namespace disjoint_set_test