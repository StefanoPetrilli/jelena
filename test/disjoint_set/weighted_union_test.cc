#include "weighted_union_test.h"
#include "block_identifier.h"

namespace disjoint_set_test {
TEST_F(WeightUnionTest, AfterInstantiation_Expect_ValueEqualToIndex) {
  EXPECT_EQ(weighted_disjoint_set_.FindBlock(kFifthBlock), kFifthBlock);
}

TEST_F(WeightUnionTest, FindBiggerThanSize_Expect_OutOfRangeException) {
  EXPECT_THROW(weighted_disjoint_set_.FindBlock(size_ + 1), std::out_of_range);
}

TEST_F(WeightUnionTest,
       AfterMergeOfEqualWeight_Expect_FirstBlockGoesIntoSecondBlock) {
  weighted_disjoint_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                     BlockIdentifier::kSecondBlock);
  auto result = weighted_disjoint_set_.FindBlock(BlockIdentifier::kSecondBlock);
  EXPECT_EQ(result, BlockIdentifier::kFirstBlock);
}

TEST_F(WeightUnionTest,
       AfterMergeOfUnequalWeight_Expect_SmallerBecomesChildOfBigger) {
  weighted_disjoint_set_.MergeBlocks(BlockIdentifier::kSecondBlock,
                                     BlockIdentifier::kThirdBlock);
  weighted_disjoint_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                     BlockIdentifier::kSecondBlock);

  EXPECT_EQ(weighted_disjoint_set_.FindBlock(BlockIdentifier::kFirstBlock),
            BlockIdentifier::kSecondBlock);
}

TEST_F(WeightUnionTest,
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

TEST_F(WeightUnionTest,
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

TEST_F(WeightUnionTest,
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

TEST_F(WeightUnionTest,
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

TEST_F(WeightUnionTest,
       AfterInstantiation_Expect_CorrectNumberOfDistinctBlocks) {
  EXPECT_EQ(weighted_disjoint_set_.GetDistinctBlocks(), size_);
}

TEST_F(WeightUnionTest, AfterMerge_Expect_CorrectDistinctBlocksValue) {
  weighted_disjoint_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                     BlockIdentifier::kSecondBlock);
  EXPECT_EQ(weighted_disjoint_set_.GetDistinctBlocks(), size_ - 1);
}

TEST_F(WeightUnionTest,
       AfterMergeOfSameBlock_Expect_CorrectDistinctBlocksValue) {
  weighted_disjoint_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                     BlockIdentifier::kSecondBlock);
  weighted_disjoint_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                     BlockIdentifier::kSecondBlock);
  EXPECT_EQ(weighted_disjoint_set_.GetDistinctBlocks(), size_ - 1);
}

TEST_F(WeightUnionTest, AfterSeveralMerges_Expect_CorrectDistinctBlocksValue) {
  weighted_disjoint_set_.MergeBlocks(BlockIdentifier::kSecondBlock,
                                     BlockIdentifier::kThirdBlock);
  weighted_disjoint_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                     BlockIdentifier::kSecondBlock);
  EXPECT_EQ(weighted_disjoint_set_.GetDistinctBlocks(), size_ - 2);
}

TEST_F(WeightUnionTest,
       AfterSeveralMerges_Expect_CorrectDistinctBlocksValue_2) {
  weighted_disjoint_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                     BlockIdentifier::kSecondBlock);
  weighted_disjoint_set_.MergeBlocks(BlockIdentifier::kSecondBlock,
                                     BlockIdentifier::kThirdBlock);
  weighted_disjoint_set_.MergeBlocks(BlockIdentifier::kThirdBlock,
                                     BlockIdentifier::kFourthBlock);
  EXPECT_EQ(weighted_disjoint_set_.GetDistinctBlocks(), size_ - 3);
}

TEST_F(WeightUnionTest,
       UsingFullCompressionAfterInstantiation_Expect_ValueEqualToIndex) {
  EXPECT_EQ(weighted_disjoint_FC_set_.FindBlock(kFifthBlock),
            kFifthBlock);
}

TEST_F(WeightUnionTest,
       UsingFullCompressionFindBiggerThanSize_Expect_OutOfRangeException) {
  EXPECT_THROW(weighted_disjoint_FC_set_.FindBlock(size_ + 1),
               std::out_of_range);
}

TEST_F(
    WeightUnionTest,
    UsingFullCompressionAfterMergeOfEqualWeight_Expect_FirstBlockGoesIntoSecondBlock) {
  weighted_disjoint_FC_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                     BlockIdentifier::kSecondBlock);
  auto result = weighted_disjoint_FC_set_.FindBlock(
      BlockIdentifier::kSecondBlock);
  EXPECT_EQ(result, BlockIdentifier::kFirstBlock);
}

TEST_F(
    WeightUnionTest,
    UsingFullCompressionAfterMergeOfUnequalWeight_Expect_SmallerBecomesChildOfBigger) {
  weighted_disjoint_FC_set_.MergeBlocks(BlockIdentifier::kSecondBlock,
                                     BlockIdentifier::kThirdBlock);
  weighted_disjoint_FC_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                     BlockIdentifier::kSecondBlock);

  EXPECT_EQ(weighted_disjoint_FC_set_.FindBlock(
                BlockIdentifier::kFirstBlock),
            BlockIdentifier::kSecondBlock);
}

TEST_F(
    WeightUnionTest,
    UsingFullCompressionAfterMultipleMergeOfUnequalWeight_Expect_SmallerBecomesChildOfBigger4) {
  //Create the first subtree
  weighted_disjoint_FC_set_.MergeBlocks(BlockIdentifier::kSecondBlock,
                                     BlockIdentifier::kThirdBlock);
  weighted_disjoint_FC_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                     BlockIdentifier::kThirdBlock);

  //Create the second subtree
  weighted_disjoint_FC_set_.MergeBlocks(BlockIdentifier::kFourthBlock,
                                     BlockIdentifier::kFifthBlock);
  weighted_disjoint_FC_set_.MergeBlocks(BlockIdentifier::kFourthBlock,
                                     BlockIdentifier::kSixthBlock);
  weighted_disjoint_FC_set_.MergeBlocks(BlockIdentifier::kFourthBlock,
                                     BlockIdentifier::kSeventhBlock);

  //Merge the two subtrees
  weighted_disjoint_FC_set_.MergeBlocks(BlockIdentifier::kSecondBlock,
                                     BlockIdentifier::kFourthBlock);

  EXPECT_EQ(weighted_disjoint_FC_set_.FindBlock(
                BlockIdentifier::kFirstBlock),
            BlockIdentifier::kFourthBlock);
}

TEST_F(
    WeightUnionTest,
    UsingFullCompressionAfterMultipleMergeOfUnequalWeight_Expect_SmallerBecomesChildOfBigger5) {
  //Create the first subtree
  weighted_disjoint_FC_set_.MergeBlocks(BlockIdentifier::kSecondBlock,
                                     BlockIdentifier::kThirdBlock);
  weighted_disjoint_FC_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                     BlockIdentifier::kThirdBlock);

  //Create the second subtree
  weighted_disjoint_FC_set_.MergeBlocks(BlockIdentifier::kFourthBlock,
                                     BlockIdentifier::kFifthBlock);
  weighted_disjoint_FC_set_.MergeBlocks(BlockIdentifier::kFourthBlock,
                                     BlockIdentifier::kSixthBlock);
  weighted_disjoint_FC_set_.MergeBlocks(BlockIdentifier::kFourthBlock,
                                     BlockIdentifier::kSeventhBlock);

  //Merge the two subtrees
  weighted_disjoint_FC_set_.MergeBlocks(BlockIdentifier::kFourthBlock,
                                     BlockIdentifier::kSecondBlock);

  EXPECT_EQ(weighted_disjoint_FC_set_.FindBlock(
                BlockIdentifier::kSixthBlock),
            BlockIdentifier::kFourthBlock);
}

TEST_F(WeightUnionTest,
       UsingPathSplittingAfterInstantiation_Expect_ValueEqualToIndex) {
  EXPECT_EQ(weighted_disjoint_PS_set_.FindBlock(kFifthBlock),
            kFifthBlock);
}

TEST_F(WeightUnionTest,
       UsingPathSplittingFindBiggerThanSize_Expect_OutOfRangeException) {
  EXPECT_THROW(weighted_disjoint_PS_set_.FindBlock(size_ + 1),
               std::out_of_range);
}

TEST_F(
    WeightUnionTest,
    UsingPathSplittingAfterMergeOfEqualWeight_Expect_FirstBlockGoesIntoSecondBlock) {
  weighted_disjoint_PS_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                     BlockIdentifier::kSecondBlock);
  auto result = weighted_disjoint_PS_set_.FindBlock(
      BlockIdentifier::kSecondBlock);
  EXPECT_EQ(result, BlockIdentifier::kFirstBlock);
}

TEST_F(
    WeightUnionTest,
    UsingPathSplittingAfterMergeOfUnequalWeight_Expect_SmallerBecomesChildOfBigger) {
  weighted_disjoint_PS_set_.MergeBlocks(BlockIdentifier::kSecondBlock,
                                     BlockIdentifier::kThirdBlock);
  weighted_disjoint_PS_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                     BlockIdentifier::kSecondBlock);

  EXPECT_EQ(weighted_disjoint_PS_set_.FindBlock(
                BlockIdentifier::kFirstBlock),
            BlockIdentifier::kSecondBlock);
}

TEST_F(
    WeightUnionTest,
    UsingPathSplittingAfterMultipleMergeOfUnequalWeight_Expect_SmallerBecomesChildOfBigger4) {
  //Create the first subtree
  weighted_disjoint_PS_set_.MergeBlocks(BlockIdentifier::kSecondBlock,
                                     BlockIdentifier::kThirdBlock);
  weighted_disjoint_PS_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                     BlockIdentifier::kThirdBlock);

  //Create the second subtree
  weighted_disjoint_PS_set_.MergeBlocks(BlockIdentifier::kFourthBlock,
                                     BlockIdentifier::kFifthBlock);
  weighted_disjoint_PS_set_.MergeBlocks(BlockIdentifier::kFourthBlock,
                                     BlockIdentifier::kSixthBlock);
  weighted_disjoint_PS_set_.MergeBlocks(BlockIdentifier::kFourthBlock,
                                     BlockIdentifier::kSeventhBlock);

  //Merge the two subtrees
  weighted_disjoint_PS_set_.MergeBlocks(BlockIdentifier::kSecondBlock,
                                     BlockIdentifier::kFourthBlock);

  EXPECT_EQ(weighted_disjoint_PS_set_.FindBlock(
                BlockIdentifier::kFirstBlock),
            BlockIdentifier::kFourthBlock);
}

TEST_F(
    WeightUnionTest,
    UsingPathSplittingAfterMultipleMergeOfUnequalWeight_Expect_SmallerBecomesChildOfBigger5) {
  //Create the first subtree
  weighted_disjoint_PS_set_.MergeBlocks(BlockIdentifier::kSecondBlock,
                                     BlockIdentifier::kThirdBlock);
  weighted_disjoint_PS_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                     BlockIdentifier::kThirdBlock);

  //Create the second subtree
  weighted_disjoint_PS_set_.MergeBlocks(BlockIdentifier::kFourthBlock,
                                     BlockIdentifier::kFifthBlock);
  weighted_disjoint_PS_set_.MergeBlocks(BlockIdentifier::kFourthBlock,
                                     BlockIdentifier::kSixthBlock);
  weighted_disjoint_PS_set_.MergeBlocks(BlockIdentifier::kFourthBlock,
                                     BlockIdentifier::kSeventhBlock);

  //Merge the two subtrees
  weighted_disjoint_PS_set_.MergeBlocks(BlockIdentifier::kFourthBlock,
                                     BlockIdentifier::kSecondBlock);

  EXPECT_EQ(weighted_disjoint_PS_set_.FindBlock(
                BlockIdentifier::kSixthBlock),
            BlockIdentifier::kFourthBlock);
}

TEST_F(WeightUnionTest,
       UsingPathHalvingAfterInstantiation_Expect_ValueEqualToIndex) {
  EXPECT_EQ(weighted_disjoint_PH_set_.FindBlock(kFifthBlock),
            kFifthBlock);
}

TEST_F(WeightUnionTest,
       UsingPathHalvingFindBiggerThanSize_Expect_OutOfRangeException) {
  EXPECT_THROW(weighted_disjoint_PH_set_.FindBlock(size_ + 1),
               std::out_of_range);
}

TEST_F(
    WeightUnionTest,
    UsingPathHalvingAfterMergeOfEqualWeight_Expect_FirstBlockGoesIntoSecondBlock) {
  weighted_disjoint_PH_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                     BlockIdentifier::kSecondBlock);
  auto result = weighted_disjoint_PH_set_.FindBlock(
      BlockIdentifier::kSecondBlock);
  EXPECT_EQ(result, BlockIdentifier::kFirstBlock);
}

TEST_F(
    WeightUnionTest,
    UsingPathHalvingAfterMergeOfUnequalWeight_Expect_SmallerBecomesChildOfBigger) {
  weighted_disjoint_PH_set_.MergeBlocks(BlockIdentifier::kSecondBlock,
                                     BlockIdentifier::kThirdBlock);
  weighted_disjoint_PH_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                     BlockIdentifier::kSecondBlock);

  EXPECT_EQ(
      weighted_disjoint_PH_set_.FindBlock(BlockIdentifier::kFirstBlock),
      BlockIdentifier::kSecondBlock);
}

TEST_F(
    WeightUnionTest,
    UsingPathHalvingAfterMultipleMergeOfUnequalWeight_Expect_SmallerBecomesChildOfBigger4) {
  //Create the first subtree
  weighted_disjoint_PH_set_.MergeBlocks(BlockIdentifier::kSecondBlock,
                                     BlockIdentifier::kThirdBlock);
  weighted_disjoint_PH_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                     BlockIdentifier::kThirdBlock);

  //Create the second subtree
  weighted_disjoint_PH_set_.MergeBlocks(BlockIdentifier::kFourthBlock,
                                     BlockIdentifier::kFifthBlock);
  weighted_disjoint_PH_set_.MergeBlocks(BlockIdentifier::kFourthBlock,
                                     BlockIdentifier::kSixthBlock);
  weighted_disjoint_PH_set_.MergeBlocks(BlockIdentifier::kFourthBlock,
                                     BlockIdentifier::kSeventhBlock);

  //Merge the two subtrees
  weighted_disjoint_PH_set_.MergeBlocks(BlockIdentifier::kSecondBlock,
                                     BlockIdentifier::kFourthBlock);

  EXPECT_EQ(
      weighted_disjoint_PH_set_.FindBlock(BlockIdentifier::kFirstBlock),
      BlockIdentifier::kFourthBlock);
}

TEST_F(
    WeightUnionTest,
    UsingPathHalvingAfterMultipleMergeOfUnequalWeight_Expect_SmallerBecomesChildOfBigger5) {
  //Create the first subtree
  weighted_disjoint_PH_set_.MergeBlocks(BlockIdentifier::kSecondBlock,
                                     BlockIdentifier::kThirdBlock);
  weighted_disjoint_PH_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                     BlockIdentifier::kThirdBlock);

  //Create the second subtree
  weighted_disjoint_PH_set_.MergeBlocks(BlockIdentifier::kFourthBlock,
                                     BlockIdentifier::kFifthBlock);
  weighted_disjoint_PH_set_.MergeBlocks(BlockIdentifier::kFourthBlock,
                                     BlockIdentifier::kSixthBlock);
  weighted_disjoint_PH_set_.MergeBlocks(BlockIdentifier::kFourthBlock,
                                     BlockIdentifier::kSeventhBlock);

  //Merge the two subtrees
  weighted_disjoint_PH_set_.MergeBlocks(BlockIdentifier::kFourthBlock,
                                     BlockIdentifier::kSecondBlock);

  EXPECT_EQ(
      weighted_disjoint_PH_set_.FindBlock(BlockIdentifier::kSixthBlock),
      BlockIdentifier::kFourthBlock);
}

#ifdef FULL_BENCHMARK
TEST_F(WeightUnionTest,
       AfterInstantiationGetTotalPathlength_Expect_CorrectValue) {
  EXPECT_EQ(weighted_disjoint_set_.GetTotalPathlength(), 0);
}

TEST_F(WeightUnionTest,
       AfterComplexMergeGetTotalPathlength_Expect_CorrectValue) {
  weighted_disjoint_set_.MergeBlocks(BlockIdentifier::kThirdBlock,
                                     BlockIdentifier::kFourthBlock);
  weighted_disjoint_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                     BlockIdentifier::kSecondBlock);
  weighted_disjoint_set_.MergeBlocks(BlockIdentifier::kFourthBlock,
                                     BlockIdentifier::kFifthBlock);
  weighted_disjoint_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                     BlockIdentifier::kNineBlock);
  weighted_disjoint_set_.MergeBlocks(BlockIdentifier::kSecondBlock,
                                     BlockIdentifier::kTenthBlock);
  weighted_disjoint_set_.MergeBlocks(BlockIdentifier::kEightBlock,
                                     BlockIdentifier::kSeventhBlock);
  EXPECT_EQ(weighted_disjoint_set_.GetTotalPathlength(), 6);
}

TEST_F(WeightUnionTest,
       AfterComplexMergeGetTotalPathlength_Expect_CorrectValue2) {
  weighted_disjoint_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                     BlockIdentifier::kSecondBlock);
  weighted_disjoint_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                     BlockIdentifier::kThirdBlock);
  weighted_disjoint_set_.MergeBlocks(BlockIdentifier::kFourthBlock,
                                     BlockIdentifier::kSixthBlock);
  weighted_disjoint_set_.MergeBlocks(BlockIdentifier::kFourthBlock,
                                     BlockIdentifier::kFifthBlock);
  weighted_disjoint_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                     BlockIdentifier::kFourthBlock);
  EXPECT_EQ(weighted_disjoint_set_.GetTotalPathlength(), 7);
}

TEST_F(
    WeightUnionTest,
    AfterComplexMergeGetFullCompressionTotalPointersUpdates_Expect_CorrectValue) {
  weighted_disjoint_FC_set_.MergeBlocks(BlockIdentifier::kThirdBlock,
                                     BlockIdentifier::kFourthBlock);
  weighted_disjoint_FC_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                     BlockIdentifier::kSecondBlock);
  weighted_disjoint_FC_set_.MergeBlocks(BlockIdentifier::kFourthBlock,
                                     BlockIdentifier::kFifthBlock);
  weighted_disjoint_FC_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                     BlockIdentifier::kNineBlock);
  weighted_disjoint_FC_set_.MergeBlocks(BlockIdentifier::kSecondBlock,
                                     BlockIdentifier::kTenthBlock);
  weighted_disjoint_FC_set_.MergeBlocks(BlockIdentifier::kEightBlock,
                                     BlockIdentifier::kSeventhBlock);
  EXPECT_EQ(weighted_disjoint_FC_set_.GetTotalPointersUpdates(), 0);
}

TEST_F(WeightUnionTest,
       AfterLinerMergeFullCompressionTotalPointersUpdates_Expect_CorrectValue) {
  weighted_disjoint_FC_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                     BlockIdentifier::kSecondBlock);
  weighted_disjoint_FC_set_.MergeBlocks(BlockIdentifier::kSecondBlock,
                                     BlockIdentifier::kThirdBlock);
  weighted_disjoint_FC_set_.MergeBlocks(BlockIdentifier::kThirdBlock,
                                     BlockIdentifier::kFourthBlock);
  EXPECT_EQ(weighted_disjoint_FC_set_.GetTotalPointersUpdates(), 0);
}

TEST_F(
    WeightUnionTest,
    AfterLinerMergeFullCompressionTotalPointersUpdates_Expect_CorrectValue2) {
  weighted_disjoint_FC_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                     BlockIdentifier::kSecondBlock);
  weighted_disjoint_FC_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                     BlockIdentifier::kThirdBlock);
  weighted_disjoint_FC_set_.MergeBlocks(BlockIdentifier::kFourthBlock,
                                     BlockIdentifier::kSixthBlock);
  weighted_disjoint_FC_set_.MergeBlocks(BlockIdentifier::kFourthBlock,
                                     BlockIdentifier::kFifthBlock);
  weighted_disjoint_FC_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                     BlockIdentifier::kFourthBlock);
  EXPECT_EQ(weighted_disjoint_FC_set_.GetTotalPointersUpdates(), 2);
}

TEST_F(
    WeightUnionTest,
    AfterComplexMergeGetPathSplittingTotalPointersUpdates_Expect_CorrectValue) {
  weighted_disjoint_PS_set_.MergeBlocks(BlockIdentifier::kThirdBlock,
                                     BlockIdentifier::kFourthBlock);
  weighted_disjoint_PS_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                     BlockIdentifier::kSecondBlock);
  weighted_disjoint_PS_set_.MergeBlocks(BlockIdentifier::kFourthBlock,
                                     BlockIdentifier::kFifthBlock);
  weighted_disjoint_PS_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                     BlockIdentifier::kNineBlock);
  weighted_disjoint_PS_set_.MergeBlocks(BlockIdentifier::kSecondBlock,
                                     BlockIdentifier::kTenthBlock);
  weighted_disjoint_PS_set_.MergeBlocks(BlockIdentifier::kEightBlock,
                                     BlockIdentifier::kSeventhBlock);
  EXPECT_EQ(weighted_disjoint_PS_set_.GetTotalPointersUpdates(), 0);
}

TEST_F(
    WeightUnionTest,
    AfterLinerMergeGetPathSplittingTotalPointersUpdates_Expect_CorrectValue) {
  weighted_disjoint_PS_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                     BlockIdentifier::kSecondBlock);
  weighted_disjoint_PS_set_.MergeBlocks(BlockIdentifier::kSecondBlock,
                                     BlockIdentifier::kThirdBlock);
  weighted_disjoint_PS_set_.MergeBlocks(BlockIdentifier::kThirdBlock,
                                     BlockIdentifier::kFourthBlock);
  EXPECT_EQ(weighted_disjoint_PS_set_.GetTotalPointersUpdates(), 0);
}

TEST_F(
    WeightUnionTest,
    AfterLinerMergeGetPathSplittingTotalPointersUpdates_Expect_CorrectValue2) {
  weighted_disjoint_PS_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                     BlockIdentifier::kSecondBlock);
  weighted_disjoint_PS_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                     BlockIdentifier::kThirdBlock);
  weighted_disjoint_PS_set_.MergeBlocks(BlockIdentifier::kFourthBlock,
                                     BlockIdentifier::kSixthBlock);
  weighted_disjoint_PS_set_.MergeBlocks(BlockIdentifier::kFourthBlock,
                                     BlockIdentifier::kFifthBlock);
  weighted_disjoint_PS_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                     BlockIdentifier::kFourthBlock);
  EXPECT_EQ(weighted_disjoint_PS_set_.GetTotalPointersUpdates(), 2);
}

TEST_F(
    WeightUnionTest,
    AfterComplexMergeGetPathHalvingTotalPointersUpdates_Expect_CorrectValue) {
  weighted_disjoint_PH_set_.MergeBlocks(BlockIdentifier::kThirdBlock,
                                     BlockIdentifier::kFourthBlock);
  weighted_disjoint_PH_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                     BlockIdentifier::kSecondBlock);
  weighted_disjoint_PH_set_.MergeBlocks(BlockIdentifier::kFourthBlock,
                                     BlockIdentifier::kFifthBlock);
  weighted_disjoint_PH_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                     BlockIdentifier::kNineBlock);
  weighted_disjoint_PH_set_.MergeBlocks(BlockIdentifier::kSecondBlock,
                                     BlockIdentifier::kTenthBlock);
  weighted_disjoint_PH_set_.MergeBlocks(BlockIdentifier::kEightBlock,
                                     BlockIdentifier::kSeventhBlock);
  EXPECT_EQ(weighted_disjoint_PH_set_.GetTotalPointersUpdates(), 0);
}

TEST_F(WeightUnionTest,
       AfterLinerMergePathHalvingonTotalPointersUpdates_Expect_CorrectValue) {
  weighted_disjoint_PH_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                     BlockIdentifier::kSecondBlock);
  weighted_disjoint_PH_set_.MergeBlocks(BlockIdentifier::kSecondBlock,
                                     BlockIdentifier::kThirdBlock);
  weighted_disjoint_PH_set_.MergeBlocks(BlockIdentifier::kThirdBlock,
                                     BlockIdentifier::kFourthBlock);
  EXPECT_EQ(weighted_disjoint_PH_set_.GetTotalPointersUpdates(), 0);
}

TEST_F(WeightUnionTest,
       AfterLinerMergePathHalvingTotalPointersUpdates_Expect_CorrectValue2) {
  weighted_disjoint_PH_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                     BlockIdentifier::kSecondBlock);
  weighted_disjoint_PH_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                     BlockIdentifier::kThirdBlock);
  weighted_disjoint_PH_set_.MergeBlocks(BlockIdentifier::kFourthBlock,
                                     BlockIdentifier::kSixthBlock);
  weighted_disjoint_PH_set_.MergeBlocks(BlockIdentifier::kFourthBlock,
                                     BlockIdentifier::kFifthBlock);
  weighted_disjoint_PH_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                     BlockIdentifier::kFourthBlock);
  EXPECT_EQ(weighted_disjoint_PH_set_.GetTotalPointersUpdates(), 2);
}
#endif

}  // namespace disjoint_set_test