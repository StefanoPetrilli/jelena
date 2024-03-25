
#include "disjoint_set_benchmark.h"

namespace disjoint_set_benchmark {
TEST_F(DisjointSetBenchmark, QuickUnion) {
  std::ofstream outfile("benchmark/disjoint_set/outputs/quick_union.txt");

  uint16_t previous_size = 0;
  size_t cycles = 0;
  while (quick_union_set_.GetDistinctBlocks() > 1) {
    auto merge_pair = distinct_pairs.at(cycles);
    quick_union_set_.MergeBlocks(std::get<0>(merge_pair),
                                 std::get<1>(merge_pair));
    cycles++;
    if (previous_size != quick_union_set_.GetDistinctBlocks()) {
      previous_size = quick_union_set_.GetDistinctBlocks();
      outfile << cycles << " - " << quick_union_set_.GetDistinctBlocks() << " ("
              << std::get<0>(merge_pair) << "," << std::get<1>(merge_pair)
              << ")" << std::endl;
    }
  }

  outfile.close();
}

TEST_F(DisjointSetBenchmark, WeightQuickUnion) {
  std::ofstream outfile(
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
      outfile << cycles << " - " << weighted_disjoint_set_.GetDistinctBlocks()
              << " (" << std::get<0>(merge_pair) << ","
              << std::get<1>(merge_pair) << ")" << std::endl;
    }
  }

  outfile.close();
}

TEST_F(DisjointSetBenchmark, RankQuickUnion) {
  std::ofstream outfile(
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
      outfile << cycles << " - " << rank_disjoint_set_.GetDistinctBlocks()
              << " (" << std::get<0>(merge_pair) << ","
              << std::get<1>(merge_pair) << ")" << std::endl;
    }
  }

  outfile.close();
}
}  // namespace disjoint_set_benchmark