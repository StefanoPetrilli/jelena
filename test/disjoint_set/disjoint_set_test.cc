#include "disjoint_set_test.h"
#include "block_identifier.h"
#include "disjoint_set.h"
#include "rank_quick_union_test.h"
#include "weighted_quick_union_test.h"

namespace disjoint_set_test {
TEST_F(QuickUnionTest, AfterInstantiation_Expect_ValueEqualToIndex) {
  EXPECT_EQ(quick_union_set_.FindBlock(kFifthBlock), kFifthBlock);
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

TEST_F(QuickUnionTest,
       AfterInstantiation_Expect_CorrectNumberOfDistinctBlocks) {
  EXPECT_EQ(quick_union_set_.GetDistinctBlocks(), size_);
}

TEST_F(QuickUnionTest, AfterMerge_Expect_CorrectDistinctBlocksValue) {
  quick_union_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                               BlockIdentifier::kSecondBlock);
  EXPECT_EQ(quick_union_set_.GetDistinctBlocks(), size_ - 1);
}

TEST_F(QuickUnionTest,
       AfterMergeOfSameBlock_Expect_CorrectDistinctBlocksValue) {
  quick_union_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                               BlockIdentifier::kSecondBlock);
  quick_union_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                               BlockIdentifier::kSecondBlock);
  EXPECT_EQ(quick_union_set_.GetDistinctBlocks(), size_ - 1);
}

TEST_F(QuickUnionTest, AfterSeveralMerges_Expect_CorrectDistinctBlocksValue) {
  quick_union_set_.MergeBlocks(BlockIdentifier::kSecondBlock,
                               BlockIdentifier::kThirdBlock);
  quick_union_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                               BlockIdentifier::kSecondBlock);
  EXPECT_EQ(quick_union_set_.GetDistinctBlocks(), size_ - 2);
}

TEST_F(QuickUnionTest, AfterSeveralMerges_Expect_CorrectDistinctBlocksValue_2) {
  quick_union_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                               BlockIdentifier::kSecondBlock);
  quick_union_set_.MergeBlocks(BlockIdentifier::kSecondBlock,
                               BlockIdentifier::kThirdBlock);
  quick_union_set_.MergeBlocks(BlockIdentifier::kThirdBlock,
                               BlockIdentifier::kFourthBlock);
  EXPECT_EQ(quick_union_set_.GetDistinctBlocks(), size_ - 3);
}

TEST_F(QuickUnionTest,
       AfterMergeOfSameBlock_Expect_CorrectDistinctBlocksValue1) {
  quick_union_set_.MergeBlocks(BlockIdentifier::kThirdBlock,
                                     BlockIdentifier::kFourthBlock);
  quick_union_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                     BlockIdentifier::kSecondBlock);
  quick_union_set_.MergeBlocks(BlockIdentifier::kFourthBlock,
                                     BlockIdentifier::kFifthBlock);
  quick_union_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                     BlockIdentifier::kNineBlock);
  quick_union_set_.MergeBlocks(BlockIdentifier::kSecondBlock,
                                     BlockIdentifier::kTenthBlock);
  quick_union_set_.MergeBlocks(BlockIdentifier::kEightBlock,
                                     BlockIdentifier::kSeventhBlock);
  EXPECT_EQ(quick_union_set_.FindBlock(kFirstBlock), kFirstBlock);
  EXPECT_EQ(quick_union_set_.FindBlock(kSecondBlock), kFirstBlock);
  EXPECT_EQ(quick_union_set_.FindBlock(kThirdBlock), kThirdBlock);
  EXPECT_EQ(quick_union_set_.FindBlock(kFourthBlock), kThirdBlock);
  EXPECT_EQ(quick_union_set_.FindBlock(kFifthBlock), kThirdBlock);
  EXPECT_EQ(quick_union_set_.FindBlock(kSixthBlock), kSixthBlock);
  EXPECT_EQ(quick_union_set_.FindBlock(kSeventhBlock), kEightBlock);
  EXPECT_EQ(quick_union_set_.FindBlock(kEightBlock), kEightBlock);
  EXPECT_EQ(quick_union_set_.FindBlock(kNineBlock), kFirstBlock);
  EXPECT_EQ(quick_union_set_.FindBlock(kTenthBlock), kFirstBlock);
  EXPECT_EQ(quick_union_set_.GetDistinctBlocks(), 4);
}

TEST_F(QuickUnionTest,
       UsingFullCompressionAfterInstantiation_Expect_ValueEqualToIndex) {
  EXPECT_EQ(quick_union_set_.FindBlockFullCompression(kFifthBlock), kFifthBlock);
}

TEST_F(QuickUnionTest, UsingFullCompressionAfterMerge_Expect_CorrectValue) {
  quick_union_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                               BlockIdentifier::kSecondBlock);
  quick_union_set_.MergeBlocks(BlockIdentifier::kSecondBlock,
                               BlockIdentifier::kThirdBlock);
  quick_union_set_.MergeBlocks(BlockIdentifier::kThirdBlock,
                               BlockIdentifier::kFourthBlock);

  EXPECT_EQ(
      quick_union_set_.FindBlockFullCompression(BlockIdentifier::kSecondBlock),
      BlockIdentifier::kFirstBlock);
}

TEST_F(QuickUnionTest,
       UsingFullCompressionAfterSeveralMerges_Expect_CorrectValue) {
  quick_union_set_.MergeBlocks(BlockIdentifier::kSecondBlock,
                               BlockIdentifier::kThirdBlock);
  quick_union_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                               BlockIdentifier::kSecondBlock);
  EXPECT_EQ(
      quick_union_set_.FindBlockFullCompression(BlockIdentifier::kThirdBlock),
      BlockIdentifier::kFirstBlock);
}

TEST_F(QuickUnionTest, UsingFullCompressionAfterFind_Expect_CorrectValue) {

  quick_union_set_.MergeBlocks(BlockIdentifier::kThirdBlock,
                               BlockIdentifier::kFourthBlock);
  quick_union_set_.MergeBlocks(BlockIdentifier::kSecondBlock,
                               BlockIdentifier::kThirdBlock);
  quick_union_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                               BlockIdentifier::kSecondBlock);
  quick_union_set_.FindBlockFullCompression(BlockIdentifier::kFourthBlock);

  EXPECT_EQ(
      quick_union_set_.FindBlockFullCompression(BlockIdentifier::kThirdBlock),
      BlockIdentifier::kFirstBlock);
}

TEST_F(QuickUnionTest,
       UsingPathSplittingAfterInstantiation_Expect_ValueEqualToIndex) {
  quick_union_set_.MergeBlocks(BlockIdentifier::kSecondBlock,
                               BlockIdentifier::kThirdBlock);
  quick_union_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                               BlockIdentifier::kSecondBlock);
  EXPECT_EQ(quick_union_set_.FindBlockPathSplitting(kFifthBlock), kFifthBlock);
}

TEST_F(QuickUnionTest, UsingPathSplittingAfterMerge_Expect_CorrectValue) {
  quick_union_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                               BlockIdentifier::kSecondBlock);
  quick_union_set_.MergeBlocks(BlockIdentifier::kSecondBlock,
                               BlockIdentifier::kThirdBlock);
  quick_union_set_.MergeBlocks(BlockIdentifier::kThirdBlock,
                               BlockIdentifier::kFourthBlock);

  EXPECT_EQ(
      quick_union_set_.FindBlockPathSplitting(BlockIdentifier::kSecondBlock),
      BlockIdentifier::kFirstBlock);
}

TEST_F(QuickUnionTest,
       UsingPathSplittingAfterSeveralMerges_Expect_CorrectValue) {
  quick_union_set_.MergeBlocks(BlockIdentifier::kSecondBlock,
                               BlockIdentifier::kThirdBlock);
  quick_union_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                               BlockIdentifier::kSecondBlock);
  EXPECT_EQ(
      quick_union_set_.FindBlockPathSplitting(BlockIdentifier::kThirdBlock),
      BlockIdentifier::kFirstBlock);
}

TEST_F(QuickUnionTest, UsingPathSplittingAfterFind_Expect_CorrectValue) {

  quick_union_set_.MergeBlocks(BlockIdentifier::kThirdBlock,
                               BlockIdentifier::kFourthBlock);
  quick_union_set_.MergeBlocks(BlockIdentifier::kSecondBlock,
                               BlockIdentifier::kThirdBlock);
  quick_union_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                               BlockIdentifier::kSecondBlock);
  quick_union_set_.FindBlockPathSplitting(BlockIdentifier::kFourthBlock);

  EXPECT_EQ(
      quick_union_set_.FindBlockPathSplitting(BlockIdentifier::kFourthBlock),
      BlockIdentifier::kFirstBlock);
}

TEST_F(QuickUnionTest,
       UsingPathHalvingAfterInstantiation_Expect_ValueEqualToIndex) {
  quick_union_set_.MergeBlocks(BlockIdentifier::kSecondBlock,
                               BlockIdentifier::kThirdBlock);
  quick_union_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                               BlockIdentifier::kSecondBlock);
  EXPECT_EQ(quick_union_set_.FindBlockPathHalving(kFifthBlock), kFifthBlock);
}

TEST_F(QuickUnionTest, UsingPathHalvingAfterMerge_Expect_CorrectValue) {
  quick_union_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                               BlockIdentifier::kSecondBlock);
  quick_union_set_.MergeBlocks(BlockIdentifier::kSecondBlock,
                               BlockIdentifier::kThirdBlock);
  quick_union_set_.MergeBlocks(BlockIdentifier::kThirdBlock,
                               BlockIdentifier::kFourthBlock);

  EXPECT_EQ(
      quick_union_set_.FindBlockPathHalving(BlockIdentifier::kSecondBlock),
      BlockIdentifier::kFirstBlock);
}

TEST_F(QuickUnionTest, UsingPathHalvingAfterSeveralMerges_Expect_CorrectValue) {
  quick_union_set_.MergeBlocks(BlockIdentifier::kSecondBlock,
                               BlockIdentifier::kThirdBlock);
  quick_union_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                               BlockIdentifier::kSecondBlock);
  EXPECT_EQ(quick_union_set_.FindBlockPathHalving(BlockIdentifier::kThirdBlock),
            BlockIdentifier::kFirstBlock);
}

TEST_F(QuickUnionTest, UsingPathHalvingAfterFind_Expect_CorrectValue) {

  quick_union_set_.MergeBlocks(BlockIdentifier::kThirdBlock,
                               BlockIdentifier::kFourthBlock);
  quick_union_set_.MergeBlocks(BlockIdentifier::kSecondBlock,
                               BlockIdentifier::kThirdBlock);
  quick_union_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                               BlockIdentifier::kSecondBlock);
  quick_union_set_.FindBlockPathHalving(BlockIdentifier::kFourthBlock);

  EXPECT_EQ(
      quick_union_set_.FindBlockPathHalving(BlockIdentifier::kFourthBlock),
      BlockIdentifier::kFirstBlock);
}

TEST_F(WeightQuickUnion, AfterInstantiation_Expect_ValueEqualToIndex) {
  EXPECT_EQ(weighted_disjoint_set_.FindBlock(kFifthBlock), kFifthBlock);
}

TEST_F(WeightQuickUnion, FindBiggerThanSize_Expect_OutOfRangeException) {
  EXPECT_THROW(weighted_disjoint_set_.FindBlock(size_ + 1), std::out_of_range);
}

TEST_F(WeightQuickUnion,
       AfterMergeOfEqualWeight_Expect_FirstBlockGoesIntoSecondBlock) {
  weighted_disjoint_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                     BlockIdentifier::kSecondBlock);
  auto result = weighted_disjoint_set_.FindBlock(BlockIdentifier::kSecondBlock);
  EXPECT_EQ(result, BlockIdentifier::kFirstBlock);
}

TEST_F(WeightQuickUnion,
       AfterMergeOfUnequalWeight_Expect_SmallerBecomesChildOfBigger) {
  weighted_disjoint_set_.MergeBlocks(BlockIdentifier::kSecondBlock,
                                     BlockIdentifier::kThirdBlock);
  weighted_disjoint_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                     BlockIdentifier::kSecondBlock);

  EXPECT_EQ(weighted_disjoint_set_.FindBlock(BlockIdentifier::kFirstBlock),
            BlockIdentifier::kSecondBlock);
}

TEST_F(WeightQuickUnion,
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

TEST_F(WeightQuickUnion,
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

TEST_F(WeightQuickUnion,
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

TEST_F(WeightQuickUnion,
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

TEST_F(WeightQuickUnion,
       AfterInstantiation_Expect_CorrectNumberOfDistinctBlocks) {
  EXPECT_EQ(weighted_disjoint_set_.GetDistinctBlocks(), size_);
}

TEST_F(WeightQuickUnion, AfterMerge_Expect_CorrectDistinctBlocksValue) {
  weighted_disjoint_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                     BlockIdentifier::kSecondBlock);
  EXPECT_EQ(weighted_disjoint_set_.GetDistinctBlocks(), size_ - 1);
}

TEST_F(WeightQuickUnion,
       AfterMergeOfSameBlock_Expect_CorrectDistinctBlocksValue) {
  weighted_disjoint_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                     BlockIdentifier::kSecondBlock);
  weighted_disjoint_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                     BlockIdentifier::kSecondBlock);
  EXPECT_EQ(weighted_disjoint_set_.GetDistinctBlocks(), size_ - 1);
}

TEST_F(WeightQuickUnion, AfterSeveralMerges_Expect_CorrectDistinctBlocksValue) {
  weighted_disjoint_set_.MergeBlocks(BlockIdentifier::kSecondBlock,
                                     BlockIdentifier::kThirdBlock);
  weighted_disjoint_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                     BlockIdentifier::kSecondBlock);
  EXPECT_EQ(weighted_disjoint_set_.GetDistinctBlocks(), size_ - 2);
}

TEST_F(WeightQuickUnion,
       AfterSeveralMerges_Expect_CorrectDistinctBlocksValue_2) {
  weighted_disjoint_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                     BlockIdentifier::kSecondBlock);
  weighted_disjoint_set_.MergeBlocks(BlockIdentifier::kSecondBlock,
                                     BlockIdentifier::kThirdBlock);
  weighted_disjoint_set_.MergeBlocks(BlockIdentifier::kThirdBlock,
                                     BlockIdentifier::kFourthBlock);
  EXPECT_EQ(weighted_disjoint_set_.GetDistinctBlocks(), size_ - 3);
}

TEST_F(WeightQuickUnion,
       UsingFullCompressionAfterInstantiation_Expect_ValueEqualToIndex) {
  EXPECT_EQ(weighted_disjoint_set_.FindBlockFullCompression(kFifthBlock), kFifthBlock);
}

TEST_F(WeightQuickUnion,
       UsingFullCompressionFindBiggerThanSize_Expect_OutOfRangeException) {
  EXPECT_THROW(weighted_disjoint_set_.FindBlockFullCompression(size_ + 1),
               std::out_of_range);
}

TEST_F(
    WeightQuickUnion,
    UsingFullCompressionAfterMergeOfEqualWeight_Expect_FirstBlockGoesIntoSecondBlock) {
  weighted_disjoint_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                     BlockIdentifier::kSecondBlock);
  auto result = weighted_disjoint_set_.FindBlockFullCompression(
      BlockIdentifier::kSecondBlock);
  EXPECT_EQ(result, BlockIdentifier::kFirstBlock);
}

TEST_F(
    WeightQuickUnion,
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
    WeightQuickUnion,
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
    WeightQuickUnion,
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

TEST_F(WeightQuickUnion,
       UsingPathSplittingAfterInstantiation_Expect_ValueEqualToIndex) {
  EXPECT_EQ(weighted_disjoint_set_.FindBlockPathSplitting(kFifthBlock), kFifthBlock);
}

TEST_F(WeightQuickUnion,
       UsingPathSplittingFindBiggerThanSize_Expect_OutOfRangeException) {
  EXPECT_THROW(weighted_disjoint_set_.FindBlockPathSplitting(size_ + 1),
               std::out_of_range);
}

TEST_F(
    WeightQuickUnion,
    UsingPathSplittingAfterMergeOfEqualWeight_Expect_FirstBlockGoesIntoSecondBlock) {
  weighted_disjoint_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                     BlockIdentifier::kSecondBlock);
  auto result = weighted_disjoint_set_.FindBlockPathSplitting(
      BlockIdentifier::kSecondBlock);
  EXPECT_EQ(result, BlockIdentifier::kFirstBlock);
}

TEST_F(
    WeightQuickUnion,
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
    WeightQuickUnion,
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
    WeightQuickUnion,
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

TEST_F(WeightQuickUnion,
       UsingPathHalvingAfterInstantiation_Expect_ValueEqualToIndex) {
  EXPECT_EQ(weighted_disjoint_set_.FindBlockPathHalving(kFifthBlock), kFifthBlock);
}

TEST_F(WeightQuickUnion,
       UsingPathHalvingFindBiggerThanSize_Expect_OutOfRangeException) {
  EXPECT_THROW(weighted_disjoint_set_.FindBlockPathHalving(size_ + 1),
               std::out_of_range);
}

TEST_F(
    WeightQuickUnion,
    UsingPathHalvingAfterMergeOfEqualWeight_Expect_FirstBlockGoesIntoSecondBlock) {
  weighted_disjoint_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                     BlockIdentifier::kSecondBlock);
  auto result = weighted_disjoint_set_.FindBlockPathHalving(
      BlockIdentifier::kSecondBlock);
  EXPECT_EQ(result, BlockIdentifier::kFirstBlock);
}

TEST_F(
    WeightQuickUnion,
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
    WeightQuickUnion,
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
    WeightQuickUnion,
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
  EXPECT_EQ(rank_disjoint_set_.FindBlockFullCompression(kFifthBlock), kFifthBlock);
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
  EXPECT_EQ(rank_disjoint_set_.FindBlockPathSplitting(kFifthBlock), kFifthBlock);
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
}  // namespace disjoint_set_test