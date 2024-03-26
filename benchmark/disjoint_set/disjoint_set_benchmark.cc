
#include "disjoint_set_benchmark.h"

namespace disjoint_set_benchmark {
TEST_F(DisjointSetBenchmark, QuickUnion) {
  std::ofstream statistics_file(
      "benchmark/disjoint_set/outputs/quick_union.txt");
  std::ofstream sequence_file("benchmark/disjoint_set/outputs/sequence.txt");

  uint16_t previous_size = 0;
  size_t cycles = 0;
  while (quick_union_set_.GetDistinctBlocks() > 1) {
    auto merge_pair = distinct_pairs.at(cycles);
    quick_union_set_.MergeBlocks(std::get<0>(merge_pair),
                                 std::get<1>(merge_pair));
    sequence_file << std::get<0>(merge_pair) << " " << std::get<1>(merge_pair)
                  << std::endl;
    cycles++;
    if (previous_size != quick_union_set_.GetDistinctBlocks()) {
      previous_size = quick_union_set_.GetDistinctBlocks();
      statistics_file << cycles << ", " << quick_union_set_.GetDistinctBlocks()
                      << ", " << quick_union_set_.GetTotalPathLenght() << ", ("
                      << std::get<0>(merge_pair) << ", "
                      << std::get<1>(merge_pair) << ")" << std::endl;
    }
  }

  statistics_file.close();
}

TEST_F(DisjointSetBenchmark, WeightQuickUnion) {
  std::ofstream statistics_file(
      "benchmark/disjoint_set/outputs/weight_quick_union.txt");

  uint16_t previous_size = 0;
  size_t cycles = 0;
  while (weighted_disjoint_set_.GetDistinctBlocks() > 1) {
    auto merge_pair = distinct_pairs.at(cycles);
    weighted_disjoint_set_.MergeBlocks(std::get<0>(merge_pair),
                                       std::get<1>(merge_pair));
    cycles++;
    if (previous_size != weighted_disjoint_set_.GetDistinctBlocks()) {
      previous_size = weighted_disjoint_set_.GetDistinctBlocks();
      statistics_file << cycles << ", "
                      << weighted_disjoint_set_.GetDistinctBlocks() << ", "
                      << weighted_disjoint_set_.GetTotalPathLenght() << ", ("
                      << std::get<0>(merge_pair) << ", "
                      << std::get<1>(merge_pair) << ")" << std::endl;
    }
  }

  statistics_file.close();
}

TEST_F(DisjointSetBenchmark, RankQuickUnion) {
  std::ofstream statistics_file(
      "benchmark/disjoint_set/outputs/rank_quick_union.txt");

  uint16_t previous_size = 0;
  size_t cycles = 0;
  while (rank_disjoint_set_.GetDistinctBlocks() > 1) {
    auto merge_pair = distinct_pairs.at(cycles);
    rank_disjoint_set_.MergeBlocks(std::get<0>(merge_pair),
                                   std::get<1>(merge_pair));
    cycles++;
    if (previous_size != rank_disjoint_set_.GetDistinctBlocks()) {
      previous_size = rank_disjoint_set_.GetDistinctBlocks();
      statistics_file << cycles << ", "
                      << rank_disjoint_set_.GetDistinctBlocks() << ", "
                      << rank_disjoint_set_.GetTotalPathLenght() << ", ("
                      << std::get<0>(merge_pair) << ", "
                      << std::get<1>(merge_pair) << ")" << std::endl;
    }
  }

  statistics_file.close();
}
}  // namespace disjoint_set_benchmark