#include "quick_union_test.h"
#include "block_identifier.h"

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
  EXPECT_EQ(quick_union_set_.FindBlock(BlockIdentifier::kFirstBlock),
            BlockIdentifier::kSecondBlock);
}

TEST_F(QuickUnionTest, AfterSeveralMerges_Expect_CorrectValue) {
  quick_union_set_.MergeBlocks(BlockIdentifier::kSecondBlock,
                               BlockIdentifier::kThirdBlock);
  quick_union_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                               BlockIdentifier::kSecondBlock);
  EXPECT_EQ(quick_union_set_.FindBlock(BlockIdentifier::kFirstBlock),
            BlockIdentifier::kThirdBlock);
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

TEST_F(QuickUnionTest, AfterComplexMerge_Expect_CorrectDistinctBlocksValue) {
  quick_union_set_.MergeBlocks(BlockIdentifier::kFourthBlock,
                               BlockIdentifier::kThirdBlock);
  quick_union_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                               BlockIdentifier::kSecondBlock);
  quick_union_set_.MergeBlocks(BlockIdentifier::kFourthBlock,
                               BlockIdentifier::kFifthBlock);
  quick_union_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                               BlockIdentifier::kNinthBlock);
  quick_union_set_.MergeBlocks(BlockIdentifier::kSecondBlock,
                               BlockIdentifier::kTenthBlock);
  quick_union_set_.MergeBlocks(BlockIdentifier::kSeventhBlock,
                               BlockIdentifier::kEightBlock);
  EXPECT_EQ(quick_union_set_.FindBlock(kFirstBlock), kTenthBlock);
  EXPECT_EQ(quick_union_set_.FindBlock(kSecondBlock), kTenthBlock);
  EXPECT_EQ(quick_union_set_.FindBlock(kThirdBlock), kFifthBlock);
  EXPECT_EQ(quick_union_set_.FindBlock(kFourthBlock), kFifthBlock);
  EXPECT_EQ(quick_union_set_.FindBlock(kFifthBlock), kFifthBlock);
  EXPECT_EQ(quick_union_set_.FindBlock(kSixthBlock), kSixthBlock);
  EXPECT_EQ(quick_union_set_.FindBlock(kSeventhBlock), kEightBlock);
  EXPECT_EQ(quick_union_set_.FindBlock(kEightBlock), kEightBlock);
  EXPECT_EQ(quick_union_set_.FindBlock(kNinthBlock), kTenthBlock);
  EXPECT_EQ(quick_union_set_.FindBlock(kTenthBlock), kTenthBlock);
  EXPECT_EQ(quick_union_set_.GetDistinctBlocks(), 4);
}

TEST_F(QuickUnionTest,
       UsingFullCompressionAfterInstantiation_Expect_ValueEqualToIndex) {
  EXPECT_EQ(quick_union_FC_set_.FindBlock(kFifthBlock), kFifthBlock);
}

TEST_F(QuickUnionTest, UsingFullCompressionAfterMerge_Expect_CorrectValue) {
  quick_union_FC_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                  BlockIdentifier::kSecondBlock);
  quick_union_FC_set_.MergeBlocks(BlockIdentifier::kSecondBlock,
                                  BlockIdentifier::kThirdBlock);
  quick_union_FC_set_.MergeBlocks(BlockIdentifier::kThirdBlock,
                                  BlockIdentifier::kFourthBlock);

  EXPECT_EQ(quick_union_FC_set_.FindBlock(BlockIdentifier::kFirstBlock),
            BlockIdentifier::kFourthBlock);
}

TEST_F(QuickUnionTest,
       UsingFullCompressionAfterSeveralMerges_Expect_CorrectValue) {
  quick_union_FC_set_.MergeBlocks(BlockIdentifier::kSecondBlock,
                                  BlockIdentifier::kThirdBlock);
  quick_union_FC_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                  BlockIdentifier::kSecondBlock);
  EXPECT_EQ(quick_union_FC_set_.FindBlock(BlockIdentifier::kFirstBlock),
            BlockIdentifier::kThirdBlock);
}

TEST_F(QuickUnionTest, UsingFullCompressionAfterFind_Expect_CorrectValue) {

  quick_union_FC_set_.MergeBlocks(BlockIdentifier::kThirdBlock,
                                  BlockIdentifier::kFourthBlock);
  quick_union_FC_set_.MergeBlocks(BlockIdentifier::kSecondBlock,
                                  BlockIdentifier::kFirstBlock);
  quick_union_FC_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                  BlockIdentifier::kSecondBlock);
  quick_union_FC_set_.FindBlock(BlockIdentifier::kFourthBlock);

  EXPECT_EQ(quick_union_FC_set_.FindBlock(BlockIdentifier::kFirstBlock),
            BlockIdentifier::kFirstBlock);
}

TEST_F(QuickUnionTest,
       UsingPathSplittingAfterInstantiation_Expect_ValueEqualToIndex) {
  quick_union_PS_set_.MergeBlocks(BlockIdentifier::kSecondBlock,
                                  BlockIdentifier::kThirdBlock);
  quick_union_PS_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                  BlockIdentifier::kSecondBlock);
  EXPECT_EQ(quick_union_PS_set_.FindBlock(kFifthBlock), kFifthBlock);
}

TEST_F(QuickUnionTest, UsingPathSplittingAfterMerge_Expect_CorrectValue) {
  quick_union_PS_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                  BlockIdentifier::kSecondBlock);
  quick_union_PS_set_.MergeBlocks(BlockIdentifier::kSecondBlock,
                                  BlockIdentifier::kThirdBlock);
  quick_union_PS_set_.MergeBlocks(BlockIdentifier::kThirdBlock,
                                  BlockIdentifier::kFourthBlock);

  EXPECT_EQ(quick_union_PS_set_.FindBlock(BlockIdentifier::kSecondBlock),
            BlockIdentifier::kFourthBlock);
}

TEST_F(QuickUnionTest,
       UsingPathSplittingAfterSeveralMerges_Expect_CorrectValue) {
  quick_union_PS_set_.MergeBlocks(BlockIdentifier::kSecondBlock,
                                  BlockIdentifier::kThirdBlock);
  quick_union_PS_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                  BlockIdentifier::kSecondBlock);
  EXPECT_EQ(quick_union_PS_set_.FindBlock(BlockIdentifier::kFirstBlock),
            BlockIdentifier::kThirdBlock);
}

TEST_F(QuickUnionTest, UsingPathSplittingAfterFind_Expect_CorrectValue) {
  quick_union_PS_set_.MergeBlocks(BlockIdentifier::kFourthBlock,
                                  BlockIdentifier::kThirdBlock);
  quick_union_PS_set_.MergeBlocks(BlockIdentifier::kThirdBlock,
                                  BlockIdentifier::kSecondBlock);
  quick_union_PS_set_.MergeBlocks(BlockIdentifier::kSecondBlock,
                                  BlockIdentifier::kFirstBlock);
  quick_union_PS_set_.FindBlock(BlockIdentifier::kFourthBlock);

  EXPECT_EQ(quick_union_PS_set_.FindBlock(BlockIdentifier::kFourthBlock),
            BlockIdentifier::kFirstBlock);
}

TEST_F(QuickUnionTest,
       UsingPathHalvingAfterInstantiation_Expect_ValueEqualToIndex) {
  EXPECT_EQ(quick_union_FH_set_.FindBlock(kFifthBlock), kFifthBlock);
}

TEST_F(QuickUnionTest, UsingPathHalvingAfterMerge_Expect_CorrectValue) {
  quick_union_FH_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                  BlockIdentifier::kSecondBlock);
  quick_union_FH_set_.MergeBlocks(BlockIdentifier::kSecondBlock,
                                  BlockIdentifier::kThirdBlock);
  quick_union_FH_set_.MergeBlocks(BlockIdentifier::kThirdBlock,
                                  BlockIdentifier::kFourthBlock);

  EXPECT_EQ(quick_union_FH_set_.FindBlock(BlockIdentifier::kFirstBlock),
            BlockIdentifier::kFourthBlock);
}

TEST_F(QuickUnionTest, UsingPathHalvingAfterSeveralMerges_Expect_CorrectValue) {
  quick_union_FH_set_.MergeBlocks(BlockIdentifier::kSecondBlock,
                                  BlockIdentifier::kThirdBlock);
  quick_union_FH_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                  BlockIdentifier::kSecondBlock);
  EXPECT_EQ(quick_union_FH_set_.FindBlock(BlockIdentifier::kFirstBlock),
            BlockIdentifier::kThirdBlock);
}

TEST_F(QuickUnionTest, UsingPathHalvingAfterFind_Expect_CorrectValue) {
  quick_union_FH_set_.MergeBlocks(BlockIdentifier::kFourthBlock,
                                  BlockIdentifier::kThirdBlock);
  quick_union_FH_set_.MergeBlocks(BlockIdentifier::kThirdBlock,
                                  BlockIdentifier::kSecondBlock);
  quick_union_FH_set_.MergeBlocks(BlockIdentifier::kSecondBlock,
                                  BlockIdentifier::kFirstBlock);
  quick_union_FH_set_.FindBlock(BlockIdentifier::kFirstBlock);

  EXPECT_EQ(quick_union_FH_set_.FindBlock(BlockIdentifier::kFourthBlock),
            BlockIdentifier::kFirstBlock);
}

#ifdef DISJOINT_SET_BENCHMARK
TEST_F(QuickUnionTest,
       AfterInstantiationGetTotalPathlength_Expect_CorrectValue) {

  EXPECT_EQ(quick_union_set_.GetTotalPathlength(), 0);
}

TEST_F(QuickUnionTest,
       AfterComplexMergeGetTotalPathlength_Expect_CorrectValue) {
  quick_union_set_.MergeBlocks(BlockIdentifier::kFourthBlock,
                               BlockIdentifier::kThirdBlock);
  quick_union_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                               BlockIdentifier::kSecondBlock);
  quick_union_set_.MergeBlocks(BlockIdentifier::kFourthBlock,
                               BlockIdentifier::kFifthBlock);
  quick_union_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                               BlockIdentifier::kNinthBlock);
  quick_union_set_.MergeBlocks(BlockIdentifier::kSecondBlock,
                               BlockIdentifier::kTenthBlock);
  quick_union_set_.MergeBlocks(BlockIdentifier::kSeventhBlock,
                               BlockIdentifier::kEightBlock);
  EXPECT_EQ(quick_union_set_.GetTotalPathlength(), 10);
}

TEST_F(QuickUnionTest,
       AfterComplexMergeGetTotalPathlength_Expect_CorrectValue2) {
  quick_union_set_.MergeBlocks(BlockIdentifier::kSeventhBlock,
                               BlockIdentifier::kFifthBlock);
  quick_union_set_.MergeBlocks(BlockIdentifier::kFifthBlock,
                               BlockIdentifier::kFourthBlock);
  quick_union_set_.MergeBlocks(BlockIdentifier::kSixthBlock,
                               BlockIdentifier::kFourthBlock);
  quick_union_set_.MergeBlocks(BlockIdentifier::kFourthBlock,
                               BlockIdentifier::kFirstBlock);
  quick_union_set_.MergeBlocks(BlockIdentifier::kThirdBlock,
                               BlockIdentifier::kFirstBlock);
  quick_union_set_.MergeBlocks(BlockIdentifier::kSecondBlock,
                               BlockIdentifier::kFirstBlock);
  EXPECT_EQ(quick_union_set_.GetTotalPathlength(), 10);
}

TEST_F(QuickUnionTest, AfterLinerMergeGetTotalPathLength_Expect_CorrectValue) {
  quick_union_set_.MergeBlocks(BlockIdentifier::kFourthBlock,
                               BlockIdentifier::kThirdBlock);
  quick_union_set_.MergeBlocks(BlockIdentifier::kThirdBlock,
                               BlockIdentifier::kSecondBlock);
  quick_union_set_.MergeBlocks(BlockIdentifier::kSecondBlock,
                               BlockIdentifier::kFirstBlock);
  EXPECT_EQ(quick_union_set_.GetTotalPathlength(), 6);
}

TEST_F(
    QuickUnionTest,
    AfterComplexMergeGetFullCompressionTotalPointersUpdates_Expect_CorrectValue) {
  quick_union_FC_set_.MergeBlocks(BlockIdentifier::kFourthBlock,
                                  BlockIdentifier::kThirdBlock);
  quick_union_FC_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                  BlockIdentifier::kSecondBlock);
  quick_union_FC_set_.MergeBlocks(BlockIdentifier::kFourthBlock,
                                  BlockIdentifier::kFifthBlock);
  quick_union_FC_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                  BlockIdentifier::kNinthBlock);
  quick_union_FC_set_.MergeBlocks(BlockIdentifier::kSecondBlock,
                                  BlockIdentifier::kTenthBlock);
  quick_union_FC_set_.MergeBlocks(BlockIdentifier::kSeventhBlock,
                                  BlockIdentifier::kEightBlock);
  EXPECT_EQ(quick_union_FC_set_.GetTotalPointersUpdates(), 4);
}

TEST_F(
    QuickUnionTest,
    AfterComplexMergeGetFullCompressionTotalPointersUpdates_Expect_CorrectValue2) {
  quick_union_FC_set_.MergeBlocks(BlockIdentifier::kSeventhBlock,
                                  BlockIdentifier::kFifthBlock);
  quick_union_FC_set_.MergeBlocks(BlockIdentifier::kFifthBlock,
                                  BlockIdentifier::kFourthBlock);
  quick_union_FC_set_.MergeBlocks(BlockIdentifier::kSixthBlock,
                                  BlockIdentifier::kFourthBlock);
  quick_union_FC_set_.MergeBlocks(BlockIdentifier::kFourthBlock,
                                  BlockIdentifier::kFirstBlock);
  quick_union_FC_set_.MergeBlocks(BlockIdentifier::kThirdBlock,
                                  BlockIdentifier::kFirstBlock);
  quick_union_FC_set_.MergeBlocks(BlockIdentifier::kSecondBlock,
                                  BlockIdentifier::kFirstBlock);
  EXPECT_EQ(quick_union_FC_set_.GetTotalPointersUpdates(), 4);
}

TEST_F(QuickUnionTest,
       AfterLinerMergeFullCompressionTotalPointersUpdates_Expect_CorrectValue) {
  quick_union_FC_set_.MergeBlocks(BlockIdentifier::kFourthBlock,
                                  BlockIdentifier::kThirdBlock);
  quick_union_FC_set_.MergeBlocks(BlockIdentifier::kThirdBlock,
                                  BlockIdentifier::kSecondBlock);
  quick_union_FC_set_.MergeBlocks(BlockIdentifier::kSecondBlock,
                                  BlockIdentifier::kFirstBlock);
  EXPECT_EQ(quick_union_FC_set_.GetTotalPointersUpdates(), 3);
}

TEST_F(
    QuickUnionTest,
    AfterComplexMergeGetPathSplittingTotalPointersUpdates_Expect_CorrectValue) {
  quick_union_PS_set_.MergeBlocks(BlockIdentifier::kFourthBlock,
                                  BlockIdentifier::kThirdBlock);
  quick_union_PS_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                  BlockIdentifier::kSecondBlock);
  quick_union_PS_set_.MergeBlocks(BlockIdentifier::kFourthBlock,
                                  BlockIdentifier::kFifthBlock);
  quick_union_PS_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                  BlockIdentifier::kNinthBlock);
  quick_union_PS_set_.MergeBlocks(BlockIdentifier::kSecondBlock,
                                  BlockIdentifier::kTenthBlock);
  quick_union_PS_set_.MergeBlocks(BlockIdentifier::kSeventhBlock,
                                  BlockIdentifier::kEightBlock);
  EXPECT_EQ(quick_union_PS_set_.GetTotalPointersUpdates(), 4);
}

TEST_F(
    QuickUnionTest,
    AfterComplexMergeGetPathSplittingTotalPointersUpdates_Expect_CorrectValue2) {
  quick_union_PS_set_.MergeBlocks(BlockIdentifier::kSeventhBlock,
                                  BlockIdentifier::kFifthBlock);
  quick_union_PS_set_.MergeBlocks(BlockIdentifier::kFifthBlock,
                                  BlockIdentifier::kFourthBlock);
  quick_union_PS_set_.MergeBlocks(BlockIdentifier::kSixthBlock,
                                  BlockIdentifier::kFourthBlock);
  quick_union_PS_set_.MergeBlocks(BlockIdentifier::kFourthBlock,
                                  BlockIdentifier::kFirstBlock);
  quick_union_PS_set_.MergeBlocks(BlockIdentifier::kThirdBlock,
                                  BlockIdentifier::kFirstBlock);
  quick_union_PS_set_.MergeBlocks(BlockIdentifier::kSecondBlock,
                                  BlockIdentifier::kFirstBlock);
  EXPECT_EQ(quick_union_PS_set_.GetTotalPointersUpdates(), 4);
}

TEST_F(QuickUnionTest,
       AfterLinerMergePathSplittingTotalPointersUpdates_Expect_CorrectValue) {
  quick_union_PS_set_.MergeBlocks(BlockIdentifier::kFourthBlock,
                                  BlockIdentifier::kThirdBlock);
  quick_union_PS_set_.MergeBlocks(BlockIdentifier::kThirdBlock,
                                  BlockIdentifier::kSecondBlock);
  quick_union_PS_set_.MergeBlocks(BlockIdentifier::kSecondBlock,
                                  BlockIdentifier::kFirstBlock);
  EXPECT_EQ(quick_union_PS_set_.GetTotalPointersUpdates(), 3);
}

TEST_F(
    QuickUnionTest,
    AfterComplexMergeGetPathHalvingTotalPointersUpdates_Expect_CorrectValue) {
  quick_union_FH_set_.MergeBlocks(BlockIdentifier::kFourthBlock,
                                  BlockIdentifier::kThirdBlock);
  quick_union_FH_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                  BlockIdentifier::kSecondBlock);
  quick_union_FH_set_.MergeBlocks(BlockIdentifier::kFourthBlock,
                                  BlockIdentifier::kFifthBlock);
  quick_union_FH_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                  BlockIdentifier::kNinthBlock);
  quick_union_FH_set_.MergeBlocks(BlockIdentifier::kSecondBlock,
                                  BlockIdentifier::kTenthBlock);
  quick_union_FH_set_.MergeBlocks(BlockIdentifier::kSeventhBlock,
                                  BlockIdentifier::kEightBlock);
  EXPECT_EQ(quick_union_FH_set_.GetTotalPointersUpdates(), 3);
}

TEST_F(
    QuickUnionTest,
    AfterComplexMergeGetPathHalvingTotalPointersUpdates_Expect_CorrectValue2) {
  quick_union_FH_set_.MergeBlocks(BlockIdentifier::kSeventhBlock,
                                  BlockIdentifier::kFifthBlock);
  quick_union_FH_set_.MergeBlocks(BlockIdentifier::kFifthBlock,
                                  BlockIdentifier::kFourthBlock);
  quick_union_FH_set_.MergeBlocks(BlockIdentifier::kSixthBlock,
                                  BlockIdentifier::kFourthBlock);
  quick_union_FH_set_.MergeBlocks(BlockIdentifier::kFourthBlock,
                                  BlockIdentifier::kFirstBlock);
  quick_union_FH_set_.MergeBlocks(BlockIdentifier::kThirdBlock,
                                  BlockIdentifier::kFirstBlock);
  quick_union_FH_set_.MergeBlocks(BlockIdentifier::kSecondBlock,
                                  BlockIdentifier::kFirstBlock);
  EXPECT_EQ(quick_union_FH_set_.GetTotalPointersUpdates(), 3);
}

TEST_F(QuickUnionTest,
       AfterLinerMergePathHalvingTotalPointersUpdates_Expect_CorrectValue) {
  quick_union_FH_set_.MergeBlocks(BlockIdentifier::kFourthBlock,
                                  BlockIdentifier::kThirdBlock);
  quick_union_FH_set_.MergeBlocks(BlockIdentifier::kThirdBlock,
                                  BlockIdentifier::kSecondBlock);
  quick_union_FH_set_.MergeBlocks(BlockIdentifier::kSecondBlock,
                                  BlockIdentifier::kFirstBlock);
  EXPECT_EQ(quick_union_FH_set_.GetTotalPointersUpdates(), 2);
}

TEST_F(QuickUnionTest,
       AfterMultipleMergesPathHalvingTotalPointersUpdates_Expect_CorrectValue) {
  quick_union_FH_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                  BlockIdentifier::kSecondBlock);
  quick_union_FH_set_.MergeBlocks(BlockIdentifier::kThirdBlock,
                                  BlockIdentifier::kFourthBlock);
  quick_union_FH_set_.MergeBlocks(BlockIdentifier::kFifthBlock,
                                  BlockIdentifier::kSixthBlock);
  quick_union_FH_set_.MergeBlocks(BlockIdentifier::kSeventhBlock,
                                  BlockIdentifier::kEightBlock);
  quick_union_FH_set_.MergeBlocks(BlockIdentifier::kNinthBlock,
                                  BlockIdentifier::kTenthBlock);
  EXPECT_EQ(quick_union_FH_set_.GetTotalPointersUpdates(), 0);
}

TEST_F(
    QuickUnionTest,
    AfterMergingTwoLongTreesPathHalvingTotalPointersUpdates_Expect_CorrectValue) {
  // Create first long tree
  quick_union_FH_set_.MergeBlocks(BlockIdentifier::kFirstBlock,
                                  BlockIdentifier::kSecondBlock);
  quick_union_FH_set_.MergeBlocks(BlockIdentifier::kSecondBlock,
                                  BlockIdentifier::kThirdBlock);
  quick_union_FH_set_.MergeBlocks(BlockIdentifier::kThirdBlock,
                                  BlockIdentifier::kFourthBlock);
  quick_union_FH_set_.MergeBlocks(BlockIdentifier::kFourthBlock,
                                  BlockIdentifier::kFifthBlock);

  // Create second long tree
  quick_union_FH_set_.MergeBlocks(BlockIdentifier::kSixthBlock,
                                  BlockIdentifier::kSeventhBlock);
  quick_union_FH_set_.MergeBlocks(BlockIdentifier::kSeventhBlock,
                                  BlockIdentifier::kEightBlock);
  quick_union_FH_set_.MergeBlocks(BlockIdentifier::kEightBlock,
                                  BlockIdentifier::kNinthBlock);
  quick_union_FH_set_.MergeBlocks(BlockIdentifier::kNinthBlock,
                                  BlockIdentifier::kTenthBlock);

  // Merge the two trees
  quick_union_FH_set_.MergeBlocks(BlockIdentifier::kFifthBlock,
                                  BlockIdentifier::kTenthBlock);

  EXPECT_EQ(quick_union_FH_set_.GetTotalPointersUpdates(), 10);
}
#endif

}  // namespace disjoint_set_test