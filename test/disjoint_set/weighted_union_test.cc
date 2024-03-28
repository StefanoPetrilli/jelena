#include "weighted_union_test.h"
#include "block_identifier.h"

namespace disjoint_set_test {
TEST_F(WeightUnion, AfterInstantiation_Expect_ValueEqualToIndex) {
  EXPECT_EQ(weighted_disjoint_set_.FindBlock(kFifthBlock), kFifthBlock);
}

TEST_F(WeightUnion, FindBiggerThanSize_Expect_OutOfRangeException) {
  EXPECT_THROW(weighted_disjoint_set_.FindBlock(size_ + 1), std::out_of_range);
}

TEST_F(WeightUnion,
       AfterMergeOfEqualWeight_Expect_FirstBlockGoesIntoSecondBlock) {
  weighted_disjoint_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                     BlockIdentifier::kSecondBlock);
  auto result = weighted_disjoint_set_.FindBlock(BlockIdentifier::kSecondBlock);
  EXPECT_EQ(result, BlockIdentifier::kFirstBlock);
}

TEST_F(WeightUnion,
       AfterMergeOfUnequalWeight_Expect_SmallerBecomesChildOfBigger) {
  weighted_disjoint_set_.MergeBlocks(BlockIdentifier::kSecondBlock,
                                     BlockIdentifier::kThirdBlock);
  weighted_disjoint_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                     BlockIdentifier::kSecondBlock);

  EXPECT_EQ(weighted_disjoint_set_.FindBlock(BlockIdentifier::kFirstBlock),
            BlockIdentifier::kSecondBlock);
}

TEST_F(WeightUnion,
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

TEST_F(WeightUnion,
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

TEST_F(WeightUnion,
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

TEST_F(WeightUnion,
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

TEST_F(WeightUnion,
       AfterInstantiation_Expect_CorrectNumberOfDistinctBlocks) {
  EXPECT_EQ(weighted_disjoint_set_.GetDistinctBlocks(), size_);
}

TEST_F(WeightUnion, AfterMerge_Expect_CorrectDistinctBlocksValue) {
  weighted_disjoint_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                     BlockIdentifier::kSecondBlock);
  EXPECT_EQ(weighted_disjoint_set_.GetDistinctBlocks(), size_ - 1);
}

TEST_F(WeightUnion,
       AfterMergeOfSameBlock_Expect_CorrectDistinctBlocksValue) {
  weighted_disjoint_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                     BlockIdentifier::kSecondBlock);
  weighted_disjoint_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                     BlockIdentifier::kSecondBlock);
  EXPECT_EQ(weighted_disjoint_set_.GetDistinctBlocks(), size_ - 1);
}

TEST_F(WeightUnion, AfterSeveralMerges_Expect_CorrectDistinctBlocksValue) {
  weighted_disjoint_set_.MergeBlocks(BlockIdentifier::kSecondBlock,
                                     BlockIdentifier::kThirdBlock);
  weighted_disjoint_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                     BlockIdentifier::kSecondBlock);
  EXPECT_EQ(weighted_disjoint_set_.GetDistinctBlocks(), size_ - 2);
}

TEST_F(WeightUnion,
       AfterSeveralMerges_Expect_CorrectDistinctBlocksValue_2) {
  weighted_disjoint_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                     BlockIdentifier::kSecondBlock);
  weighted_disjoint_set_.MergeBlocks(BlockIdentifier::kSecondBlock,
                                     BlockIdentifier::kThirdBlock);
  weighted_disjoint_set_.MergeBlocks(BlockIdentifier::kThirdBlock,
                                     BlockIdentifier::kFourthBlock);
  EXPECT_EQ(weighted_disjoint_set_.GetDistinctBlocks(), size_ - 3);
}

TEST_F(WeightUnion,
       UsingFullCompressionAfterInstantiation_Expect_ValueEqualToIndex) {
  EXPECT_EQ(weighted_disjoint_set_.FindBlockFullCompression(kFifthBlock),
            kFifthBlock);
}

TEST_F(WeightUnion,
       UsingFullCompressionFindBiggerThanSize_Expect_OutOfRangeException) {
  EXPECT_THROW(weighted_disjoint_set_.FindBlockFullCompression(size_ + 1),
               std::out_of_range);
}

TEST_F(
    WeightUnion,
    UsingFullCompressionAfterMergeOfEqualWeight_Expect_FirstBlockGoesIntoSecondBlock) {
  weighted_disjoint_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                     BlockIdentifier::kSecondBlock);
  auto result = weighted_disjoint_set_.FindBlockFullCompression(
      BlockIdentifier::kSecondBlock);
  EXPECT_EQ(result, BlockIdentifier::kFirstBlock);
}

TEST_F(
    WeightUnion,
    UsingFullCompressionAfterMergeOfUnequalWeight_Expect_SmallerBecomesChildOfBigger) {
  weighted_disjoint_set_.MergeBlocks(BlockIdentifier::kSecondBlock,
                                     BlockIdentifier::kThirdBlock);
  weighted_disjoint_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                     BlockIdentifier::kSecondBlock);

  EXPECT_EQ(weighted_disjoint_set_.FindBlockFullCompression(
                BlockIdentifier::kFirstBlock),
            BlockIdentifier::kSecondBlock);
}

TEST_F(
    WeightUnion,
    UsingFullCompressionAfterMultipleMergeOfUnequalWeight_Expect_SmallerBecomesChildOfBigger4) {
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

  EXPECT_EQ(weighted_disjoint_set_.FindBlockFullCompression(
                BlockIdentifier::kFirstBlock),
            BlockIdentifier::kFourthBlock);
}

TEST_F(
    WeightUnion,
    UsingFullCompressionAfterMultipleMergeOfUnequalWeight_Expect_SmallerBecomesChildOfBigger5) {
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

  EXPECT_EQ(weighted_disjoint_set_.FindBlockFullCompression(
                BlockIdentifier::kSixthBlock),
            BlockIdentifier::kFourthBlock);
}

TEST_F(WeightUnion,
       UsingPathSplittingAfterInstantiation_Expect_ValueEqualToIndex) {
  EXPECT_EQ(weighted_disjoint_set_.FindBlockPathSplitting(kFifthBlock),
            kFifthBlock);
}

TEST_F(WeightUnion,
       UsingPathSplittingFindBiggerThanSize_Expect_OutOfRangeException) {
  EXPECT_THROW(weighted_disjoint_set_.FindBlockPathSplitting(size_ + 1),
               std::out_of_range);
}

TEST_F(
    WeightUnion,
    UsingPathSplittingAfterMergeOfEqualWeight_Expect_FirstBlockGoesIntoSecondBlock) {
  weighted_disjoint_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                     BlockIdentifier::kSecondBlock);
  auto result = weighted_disjoint_set_.FindBlockPathSplitting(
      BlockIdentifier::kSecondBlock);
  EXPECT_EQ(result, BlockIdentifier::kFirstBlock);
}

TEST_F(
    WeightUnion,
    UsingPathSplittingAfterMergeOfUnequalWeight_Expect_SmallerBecomesChildOfBigger) {
  weighted_disjoint_set_.MergeBlocks(BlockIdentifier::kSecondBlock,
                                     BlockIdentifier::kThirdBlock);
  weighted_disjoint_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                     BlockIdentifier::kSecondBlock);

  EXPECT_EQ(weighted_disjoint_set_.FindBlockPathSplitting(
                BlockIdentifier::kFirstBlock),
            BlockIdentifier::kSecondBlock);
}

TEST_F(
    WeightUnion,
    UsingPathSplittingAfterMultipleMergeOfUnequalWeight_Expect_SmallerBecomesChildOfBigger4) {
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

  EXPECT_EQ(weighted_disjoint_set_.FindBlockPathSplitting(
                BlockIdentifier::kFirstBlock),
            BlockIdentifier::kFourthBlock);
}

TEST_F(
    WeightUnion,
    UsingPathSplittingAfterMultipleMergeOfUnequalWeight_Expect_SmallerBecomesChildOfBigger5) {
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

  EXPECT_EQ(weighted_disjoint_set_.FindBlockPathSplitting(
                BlockIdentifier::kSixthBlock),
            BlockIdentifier::kFourthBlock);
}

TEST_F(WeightUnion,
       UsingPathHalvingAfterInstantiation_Expect_ValueEqualToIndex) {
  EXPECT_EQ(weighted_disjoint_set_.FindBlockPathHalving(kFifthBlock),
            kFifthBlock);
}

TEST_F(WeightUnion,
       UsingPathHalvingFindBiggerThanSize_Expect_OutOfRangeException) {
  EXPECT_THROW(weighted_disjoint_set_.FindBlockPathHalving(size_ + 1),
               std::out_of_range);
}

TEST_F(
    WeightUnion,
    UsingPathHalvingAfterMergeOfEqualWeight_Expect_FirstBlockGoesIntoSecondBlock) {
  weighted_disjoint_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                     BlockIdentifier::kSecondBlock);
  auto result = weighted_disjoint_set_.FindBlockPathHalving(
      BlockIdentifier::kSecondBlock);
  EXPECT_EQ(result, BlockIdentifier::kFirstBlock);
}

TEST_F(
    WeightUnion,
    UsingPathHalvingAfterMergeOfUnequalWeight_Expect_SmallerBecomesChildOfBigger) {
  weighted_disjoint_set_.MergeBlocks(BlockIdentifier::kSecondBlock,
                                     BlockIdentifier::kThirdBlock);
  weighted_disjoint_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                     BlockIdentifier::kSecondBlock);

  EXPECT_EQ(
      weighted_disjoint_set_.FindBlockPathHalving(BlockIdentifier::kFirstBlock),
      BlockIdentifier::kSecondBlock);
}

TEST_F(
    WeightUnion,
    UsingPathHalvingAfterMultipleMergeOfUnequalWeight_Expect_SmallerBecomesChildOfBigger4) {
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

  EXPECT_EQ(
      weighted_disjoint_set_.FindBlockPathHalving(BlockIdentifier::kFirstBlock),
      BlockIdentifier::kFourthBlock);
}

TEST_F(
    WeightUnion,
    UsingPathHalvingAfterMultipleMergeOfUnequalWeight_Expect_SmallerBecomesChildOfBigger5) {
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

  EXPECT_EQ(
      weighted_disjoint_set_.FindBlockPathHalving(BlockIdentifier::kSixthBlock),
      BlockIdentifier::kFourthBlock);
}

#ifdef FULL_BENCHMARK
TEST_F(WeightUnion,
       AfterInstantiationGetTotalPathlength_Expect_CorrectValue) {
  EXPECT_EQ(weighted_disjoint_set_.GetTotalPathlength(), 0);
}

TEST_F(WeightUnion,
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

TEST_F(WeightUnion,
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
    WeightUnion,
    AfterComplexMergeGetFullCompressionTotalPointersUpdates_Expect_CorrectValue) {
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
  EXPECT_EQ(weighted_disjoint_set_.GetFullCompressionTotalPointersUpdates(), 0);
}

TEST_F(WeightUnion,
       AfterLinerMergeFullCompressionTotalPointersUpdates_Expect_CorrectValue) {
  weighted_disjoint_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                     BlockIdentifier::kSecondBlock);
  weighted_disjoint_set_.MergeBlocks(BlockIdentifier::kSecondBlock,
                                     BlockIdentifier::kThirdBlock);
  weighted_disjoint_set_.MergeBlocks(BlockIdentifier::kThirdBlock,
                                     BlockIdentifier::kFourthBlock);
  EXPECT_EQ(weighted_disjoint_set_.GetFullCompressionTotalPointersUpdates(), 0);
}

TEST_F(WeightUnion,
       AfterLinerMergeFullCompressionTotalPointersUpdates_Expect_CorrectValue2) {
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
  EXPECT_EQ(weighted_disjoint_set_.GetFullCompressionTotalPointersUpdates(), 2);
}

TEST_F(
    WeightUnion,
    AfterComplexMergeGetPathSplittingTotalPointersUpdates_Expect_CorrectValue) {
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
  EXPECT_EQ(weighted_disjoint_set_.GetPathSplittingTotalPointersUpdates(), 0);
}

TEST_F(WeightUnion,
       AfterLinerMergeGetPathSplittingTotalPointersUpdates_Expect_CorrectValue) {
  weighted_disjoint_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                     BlockIdentifier::kSecondBlock);
  weighted_disjoint_set_.MergeBlocks(BlockIdentifier::kSecondBlock,
                                     BlockIdentifier::kThirdBlock);
  weighted_disjoint_set_.MergeBlocks(BlockIdentifier::kThirdBlock,
                                     BlockIdentifier::kFourthBlock);
  EXPECT_EQ(weighted_disjoint_set_.GetPathSplittingTotalPointersUpdates(), 0);
}

TEST_F(WeightUnion,
       AfterLinerMergeGetPathSplittingTotalPointersUpdates_Expect_CorrectValue2) {
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
  EXPECT_EQ(weighted_disjoint_set_.GetPathSplittingTotalPointersUpdates(), 2);
}

TEST_F(
    WeightUnion,
    AfterComplexMergeGetPathHalvingTotalPointersUpdates_Expect_CorrectValue) {
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
  EXPECT_EQ(weighted_disjoint_set_.GetPathHalvingPointersUpdates(), 0);
}

TEST_F(WeightUnion,
       AfterLinerMergePathHalvingonTotalPointersUpdates_Expect_CorrectValue) {
  weighted_disjoint_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                     BlockIdentifier::kSecondBlock);
  weighted_disjoint_set_.MergeBlocks(BlockIdentifier::kSecondBlock,
                                     BlockIdentifier::kThirdBlock);
  weighted_disjoint_set_.MergeBlocks(BlockIdentifier::kThirdBlock,
                                     BlockIdentifier::kFourthBlock);
  EXPECT_EQ(weighted_disjoint_set_.GetPathHalvingPointersUpdates(), 0);
}

TEST_F(WeightUnion,
       AfterLinerMergePathHalvingTotalPointersUpdates_Expect_CorrectValue2) {
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
  EXPECT_EQ(weighted_disjoint_set_.GetPathHalvingPointersUpdates(), 2);
}
#endif

}  // namespace disjoint_set_test