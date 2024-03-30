#include "rank_union_test.h"
#include "block_identifier.h"

namespace disjoint_set_test {
TEST_F(RankUnionTest, AfterInstantiation_Expect_ValueEqualToIndex) {
  EXPECT_EQ(rank_disjoint_set_.FindBlock(kFifthBlock), kFifthBlock);
}

TEST_F(RankUnionTest, FindBiggerThanSize_Expect_OutOfRangeException) {
  EXPECT_THROW(rank_disjoint_set_.FindBlock(size_ + 1), std::out_of_range);
}

TEST_F(RankUnionTest,
       AfterMergeOfEqualRank_Expect_FirstBlockGoesIntoSecondBlock) {
  rank_disjoint_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                 BlockIdentifier::kSecondBlock);
  auto result = rank_disjoint_set_.FindBlock(BlockIdentifier::kSecondBlock);
  EXPECT_EQ(result, BlockIdentifier::kFirstBlock);
}

TEST_F(RankUnionTest,
       AfterMergeOfUnequalRank_Expect_SmallerBecomesChildOfBigger1) {
  rank_disjoint_set_.MergeBlocks(BlockIdentifier::kSecondBlock,
                                 BlockIdentifier::kThirdBlock);
  rank_disjoint_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                 BlockIdentifier::kSecondBlock);

  EXPECT_EQ(rank_disjoint_set_.FindBlock(BlockIdentifier::kFirstBlock),
            BlockIdentifier::kSecondBlock);
}

TEST_F(RankUnionTest,
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

TEST_F(RankUnionTest,
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

TEST_F(RankUnionTest, AfterInstantiation_Expect_CorrectNumberOfDistinctBlocks) {
  EXPECT_EQ(rank_disjoint_set_.GetDistinctBlocks(), size_);
}

TEST_F(RankUnionTest, AfterMerge_Expect_CorrectDistinctBlocksValue) {
  rank_disjoint_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                 BlockIdentifier::kSecondBlock);
  EXPECT_EQ(rank_disjoint_set_.GetDistinctBlocks(), size_ - 1);
}

TEST_F(RankUnionTest, AfterMergeOfSameBlock_Expect_CorrectDistinctBlocksValue) {
  rank_disjoint_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                 BlockIdentifier::kSecondBlock);
  rank_disjoint_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                 BlockIdentifier::kSecondBlock);
  EXPECT_EQ(rank_disjoint_set_.GetDistinctBlocks(), size_ - 1);
}

TEST_F(RankUnionTest, AfterSeveralMerges_Expect_CorrectDistinctBlocksValue) {
  rank_disjoint_set_.MergeBlocks(BlockIdentifier::kSecondBlock,
                                 BlockIdentifier::kThirdBlock);
  rank_disjoint_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                 BlockIdentifier::kSecondBlock);
  EXPECT_EQ(rank_disjoint_set_.GetDistinctBlocks(), size_ - 2);
}

TEST_F(RankUnionTest, AfterSeveralMerges_Expect_CorrectDistinctBlocksValue_2) {
  rank_disjoint_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                 BlockIdentifier::kSecondBlock);
  rank_disjoint_set_.MergeBlocks(BlockIdentifier::kSecondBlock,
                                 BlockIdentifier::kThirdBlock);
  rank_disjoint_set_.MergeBlocks(BlockIdentifier::kThirdBlock,
                                 BlockIdentifier::kFourthBlock);
  EXPECT_EQ(rank_disjoint_set_.GetDistinctBlocks(), size_ - 3);
}

TEST_F(RankUnionTest,
       UsingFullCompressionAfterInstantiation_Expect_ValueEqualToIndex) {
  EXPECT_EQ(rank_disjoint_FC_set_.FindBlock(kFifthBlock), kFifthBlock);
}

TEST_F(RankUnionTest,
       UsingFullCompressionFindBiggerThanSize_Expect_OutOfRangeException) {
  EXPECT_THROW(rank_disjoint_FC_set_.FindBlock(size_ + 1), std::out_of_range);
}

TEST_F(
    RankUnionTest,
    UsingFullCompressionAfterMergeOfEqualRank_Expect_FirstBlockGoesIntoSecondBlock) {
  rank_disjoint_FC_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                    BlockIdentifier::kSecondBlock);
  auto result = rank_disjoint_FC_set_.FindBlock(BlockIdentifier::kSecondBlock);
  EXPECT_EQ(result, BlockIdentifier::kFirstBlock);
}

TEST_F(
    RankUnionTest,
    UsingFullCompressionAfterMergeOfUnequalRank_Expect_SmallerBecomesChildOfBigger1) {
  rank_disjoint_FC_set_.MergeBlocks(BlockIdentifier::kSecondBlock,
                                    BlockIdentifier::kThirdBlock);
  rank_disjoint_FC_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                    BlockIdentifier::kSecondBlock);

  EXPECT_EQ(rank_disjoint_FC_set_.FindBlock(BlockIdentifier::kFirstBlock),
            BlockIdentifier::kSecondBlock);
}

TEST_F(
    RankUnionTest,
    UsingFullCompressionAfterMergeOfUnequalRank_Expect_SmallerBecomesChildOfBigger2) {
  //Create the first subtree
  rank_disjoint_FC_set_.MergeBlocks(BlockIdentifier::kSecondBlock,
                                    BlockIdentifier::kThirdBlock);
  rank_disjoint_FC_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                    BlockIdentifier::kThirdBlock);

  //Create the second subtree
  rank_disjoint_FC_set_.MergeBlocks(BlockIdentifier::kFourthBlock,
                                    BlockIdentifier::kFifthBlock);
  rank_disjoint_FC_set_.MergeBlocks(BlockIdentifier::kFourthBlock,
                                    BlockIdentifier::kSixthBlock);

  //Merge the two subtrees
  rank_disjoint_FC_set_.MergeBlocks(BlockIdentifier::kSecondBlock,
                                    BlockIdentifier::kFourthBlock);

  EXPECT_EQ(rank_disjoint_FC_set_.FindBlock(BlockIdentifier::kSixthBlock),
            BlockIdentifier::kSecondBlock);
}

TEST_F(
    RankUnionTest,
    UsingFullCompressionAfterMergeOfUnequalRank_Expect_SmallerBecomesChildOfBigger3) {
  //Create the first subtree
  rank_disjoint_FC_set_.MergeBlocks(BlockIdentifier::kSecondBlock,
                                    BlockIdentifier::kThirdBlock);
  rank_disjoint_FC_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                    BlockIdentifier::kThirdBlock);

  //Create the second subtree
  rank_disjoint_FC_set_.MergeBlocks(BlockIdentifier::kFourthBlock,
                                    BlockIdentifier::kFifthBlock);
  rank_disjoint_FC_set_.MergeBlocks(BlockIdentifier::kFourthBlock,
                                    BlockIdentifier::kSixthBlock);
  rank_disjoint_FC_set_.MergeBlocks(BlockIdentifier::kFourthBlock,
                                    BlockIdentifier::kSeventhBlock);

  //Merge the two subtrees
  rank_disjoint_FC_set_.MergeBlocks(BlockIdentifier::kSecondBlock,
                                    BlockIdentifier::kFourthBlock);

  EXPECT_EQ(rank_disjoint_FC_set_.FindBlock(BlockIdentifier::kSixthBlock),
            BlockIdentifier::kFourthBlock);
}

TEST_F(RankUnionTest,
       UsingPathHalvingAfterInstantiation_Expect_ValueEqualToIndex) {
  EXPECT_EQ(rank_disjoint_PH_set_.FindBlock(kFifthBlock),
            kFifthBlock);
}

TEST_F(RankUnionTest,
       UsingPathHalvingFindBiggerThanSize_Expect_OutOfRangeException) {
  EXPECT_THROW(rank_disjoint_PH_set_.FindBlock(size_ + 1),
               std::out_of_range);
}

TEST_F(
    RankUnionTest,
    UsingPathHalvingAfterMergeOfEqualRank_Expect_FirstBlockGoesIntoSecondBlock) {
  rank_disjoint_PH_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                    BlockIdentifier::kSecondBlock);
  auto result =
      rank_disjoint_PH_set_.FindBlock(BlockIdentifier::kSecondBlock);
  EXPECT_EQ(result, BlockIdentifier::kFirstBlock);
}

TEST_F(
    RankUnionTest,
    UsingPathHalvingAfterMergeOfUnequalRank_Expect_SmallerBecomesChildOfBigger1) {
  rank_disjoint_PH_set_.MergeBlocks(BlockIdentifier::kSecondBlock,
                                    BlockIdentifier::kThirdBlock);
  rank_disjoint_PH_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                    BlockIdentifier::kSecondBlock);

  EXPECT_EQ(
      rank_disjoint_PH_set_.FindBlock(BlockIdentifier::kFirstBlock),
      BlockIdentifier::kSecondBlock);
}

TEST_F(
    RankUnionTest,
    UsingPathHalvingAfterMergeOfUnequalRank_Expect_SmallerBecomesChildOfBigger2) {
  //Create the first subtree
  rank_disjoint_PH_set_.MergeBlocks(BlockIdentifier::kSecondBlock,
                                    BlockIdentifier::kThirdBlock);
  rank_disjoint_PH_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                    BlockIdentifier::kThirdBlock);

  //Create the second subtree
  rank_disjoint_PH_set_.MergeBlocks(BlockIdentifier::kFourthBlock,
                                    BlockIdentifier::kFifthBlock);
  rank_disjoint_PH_set_.MergeBlocks(BlockIdentifier::kFourthBlock,
                                    BlockIdentifier::kSixthBlock);

  //Merge the two subtrees
  rank_disjoint_PH_set_.MergeBlocks(BlockIdentifier::kSecondBlock,
                                    BlockIdentifier::kFourthBlock);

  EXPECT_EQ(
      rank_disjoint_PH_set_.FindBlock(BlockIdentifier::kSixthBlock),
      BlockIdentifier::kSecondBlock);
}

TEST_F(
    RankUnionTest,
    UsingPathHalvingAfterMergeOfUnequalRank_Expect_SmallerBecomesChildOfBigger3) {
  //Create the first subtree
  rank_disjoint_PH_set_.MergeBlocks(BlockIdentifier::kSecondBlock,
                                    BlockIdentifier::kThirdBlock);
  rank_disjoint_PH_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                    BlockIdentifier::kThirdBlock);

  //Create the second subtree
  rank_disjoint_PH_set_.MergeBlocks(BlockIdentifier::kFourthBlock,
                                    BlockIdentifier::kFifthBlock);
  rank_disjoint_PH_set_.MergeBlocks(BlockIdentifier::kFourthBlock,
                                    BlockIdentifier::kSixthBlock);
  rank_disjoint_PH_set_.MergeBlocks(BlockIdentifier::kFourthBlock,
                                    BlockIdentifier::kSeventhBlock);

  //Merge the two subtrees
  rank_disjoint_PH_set_.MergeBlocks(BlockIdentifier::kSecondBlock,
                                    BlockIdentifier::kFourthBlock);

  EXPECT_EQ(
      rank_disjoint_PH_set_.FindBlock(BlockIdentifier::kSixthBlock),
      BlockIdentifier::kFourthBlock);
}

TEST_F(RankUnionTest,
       UsingPathSplittingAfterInstantiation_Expect_ValueEqualToIndex) {
  EXPECT_EQ(rank_disjoint_PS_set_.FindBlock(kFifthBlock),
            kFifthBlock);
}

TEST_F(RankUnionTest,
       UsingPathSplittingFindBiggerThanSize_Expect_OutOfRangeException) {
  EXPECT_THROW(rank_disjoint_PS_set_.FindBlock(size_ + 1),
               std::out_of_range);
}

TEST_F(
    RankUnionTest,
    UsingPathSplittingAfterMergeOfEqualRank_Expect_FirstBlockGoesIntoSecondBlock) {
  rank_disjoint_PS_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                    BlockIdentifier::kSecondBlock);
  auto result = rank_disjoint_PS_set_.FindBlock(
      BlockIdentifier::kSecondBlock);
  EXPECT_EQ(result, BlockIdentifier::kFirstBlock);
}

TEST_F(
    RankUnionTest,
    UsingPathSplittingAfterMergeOfUnequalRank_Expect_SmallerBecomesChildOfBigger1) {
  rank_disjoint_PS_set_.MergeBlocks(BlockIdentifier::kSecondBlock,
                                    BlockIdentifier::kThirdBlock);
  rank_disjoint_PS_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                    BlockIdentifier::kSecondBlock);

  EXPECT_EQ(rank_disjoint_PS_set_.FindBlock(
                BlockIdentifier::kFirstBlock),
            BlockIdentifier::kSecondBlock);
}

TEST_F(
    RankUnionTest,
    UsingPathSplittingAfterMergeOfUnequalRank_Expect_SmallerBecomesChildOfBigger2) {
  //Create the first subtree
  rank_disjoint_PS_set_.MergeBlocks(BlockIdentifier::kSecondBlock,
                                    BlockIdentifier::kThirdBlock);
  rank_disjoint_PS_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                    BlockIdentifier::kThirdBlock);

  //Create the second subtree
  rank_disjoint_PS_set_.MergeBlocks(BlockIdentifier::kFourthBlock,
                                    BlockIdentifier::kFifthBlock);
  rank_disjoint_PS_set_.MergeBlocks(BlockIdentifier::kFourthBlock,
                                    BlockIdentifier::kSixthBlock);

  //Merge the two subtrees
  rank_disjoint_PS_set_.MergeBlocks(BlockIdentifier::kSecondBlock,
                                    BlockIdentifier::kFourthBlock);

  EXPECT_EQ(rank_disjoint_PS_set_.FindBlock(
                BlockIdentifier::kSixthBlock),
            BlockIdentifier::kSecondBlock);
}

TEST_F(
    RankUnionTest,
    UsingPathSplittingAfterMergeOfUnequalRank_Expect_SmallerBecomesChildOfBigger3) {
  //Create the first subtree
  rank_disjoint_PS_set_.MergeBlocks(BlockIdentifier::kSecondBlock,
                                    BlockIdentifier::kThirdBlock);
  rank_disjoint_PS_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                    BlockIdentifier::kThirdBlock);

  //Create the second subtree
  rank_disjoint_PS_set_.MergeBlocks(BlockIdentifier::kFourthBlock,
                                    BlockIdentifier::kFifthBlock);
  rank_disjoint_PS_set_.MergeBlocks(BlockIdentifier::kFourthBlock,
                                    BlockIdentifier::kSixthBlock);
  rank_disjoint_PS_set_.MergeBlocks(BlockIdentifier::kFourthBlock,
                                    BlockIdentifier::kSeventhBlock);

  //Merge the two subtrees
  rank_disjoint_PS_set_.MergeBlocks(BlockIdentifier::kSecondBlock,
                                    BlockIdentifier::kFourthBlock);

  EXPECT_EQ(rank_disjoint_PS_set_.FindBlock(
                BlockIdentifier::kSixthBlock),
            BlockIdentifier::kFourthBlock);
}

#ifdef FULL_BENCHMARK
TEST_F(RankUnionTest,
       AfterInstantiationGetTotalPathlength_Expect_CorrectValue) {
  EXPECT_EQ(rank_disjoint_set_.GetTotalPathlength(), 0);
}

TEST_F(RankUnionTest, AfterComplexMergeGetTotalPathlength_Expect_CorrectValue) {
  rank_disjoint_set_.MergeBlocks(BlockIdentifier::kThirdBlock,
                                 BlockIdentifier::kFourthBlock);
  rank_disjoint_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                 BlockIdentifier::kSecondBlock);
  rank_disjoint_set_.MergeBlocks(BlockIdentifier::kFourthBlock,
                                 BlockIdentifier::kFifthBlock);
  rank_disjoint_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                 BlockIdentifier::kNinthBlock);
  rank_disjoint_set_.MergeBlocks(BlockIdentifier::kSecondBlock,
                                 BlockIdentifier::kTenthBlock);
  rank_disjoint_set_.MergeBlocks(BlockIdentifier::kEightBlock,
                                 BlockIdentifier::kSeventhBlock);
  EXPECT_EQ(rank_disjoint_set_.GetTotalPathlength(), 6);
}

TEST_F(RankUnionTest,
       AfterComplexMergeGetTotalPathlength_Expect_CorrectValue2) {
  rank_disjoint_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                 BlockIdentifier::kSecondBlock);
  rank_disjoint_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                 BlockIdentifier::kThirdBlock);
  rank_disjoint_set_.MergeBlocks(BlockIdentifier::kFourthBlock,
                                 BlockIdentifier::kSixthBlock);
  rank_disjoint_set_.MergeBlocks(BlockIdentifier::kFourthBlock,
                                 BlockIdentifier::kFifthBlock);
  rank_disjoint_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                 BlockIdentifier::kFourthBlock);
  EXPECT_EQ(rank_disjoint_set_.GetTotalPathlength(), 7);
}

TEST_F(
    RankUnionTest,
    AfterComplexMergeGetFullCompressionTotalPointersUpdates_Expect_CorrectValue) {
  rank_disjoint_FC_set_.MergeBlocks(BlockIdentifier::kThirdBlock,
                                    BlockIdentifier::kFourthBlock);
  rank_disjoint_FC_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                    BlockIdentifier::kSecondBlock);
  rank_disjoint_FC_set_.MergeBlocks(BlockIdentifier::kFourthBlock,
                                    BlockIdentifier::kFifthBlock);
  rank_disjoint_FC_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                    BlockIdentifier::kNinthBlock);
  rank_disjoint_FC_set_.MergeBlocks(BlockIdentifier::kSecondBlock,
                                    BlockIdentifier::kTenthBlock);
  rank_disjoint_FC_set_.MergeBlocks(BlockIdentifier::kEightBlock,
                                    BlockIdentifier::kSeventhBlock);
  EXPECT_EQ(rank_disjoint_FC_set_.GetTotalPointersUpdates(), 0);
}

TEST_F(RankUnionTest,
       AfterLinerMergeFullCompressionTotalPointersUpdates_Expect_CorrectValue) {
  rank_disjoint_FC_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                    BlockIdentifier::kSecondBlock);
  rank_disjoint_FC_set_.MergeBlocks(BlockIdentifier::kSecondBlock,
                                    BlockIdentifier::kThirdBlock);
  rank_disjoint_FC_set_.MergeBlocks(BlockIdentifier::kThirdBlock,
                                    BlockIdentifier::kFourthBlock);
  EXPECT_EQ(rank_disjoint_FC_set_.GetTotalPointersUpdates(), 0);
}

TEST_F(
    RankUnionTest,
    AfterLinerMergeFullCompressionTotalPointersUpdates_Expect_CorrectValue2) {
  rank_disjoint_FC_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                    BlockIdentifier::kSecondBlock);
  rank_disjoint_FC_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                    BlockIdentifier::kThirdBlock);
  rank_disjoint_FC_set_.MergeBlocks(BlockIdentifier::kFourthBlock,
                                    BlockIdentifier::kSixthBlock);
  rank_disjoint_FC_set_.MergeBlocks(BlockIdentifier::kFourthBlock,
                                    BlockIdentifier::kFifthBlock);
  rank_disjoint_FC_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                    BlockIdentifier::kFourthBlock);
  EXPECT_EQ(rank_disjoint_FC_set_.GetTotalPointersUpdates(), 2);
}
#endif

}  // namespace disjoint_set_test