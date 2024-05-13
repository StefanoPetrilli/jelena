#include "disjoint_set_benchmark.h"

namespace disjoint_set_benchmark {
#ifdef DISJOINT_SET_BENCHMARK
std::ofstream DisjointSetBenchmark::quick_union_statistics_;
std::ofstream DisjointSetBenchmark::quick_union_FC_statistics_;
std::ofstream DisjointSetBenchmark::quick_union_PS_statistics_;
std::ofstream DisjointSetBenchmark::quick_union_PH_statistics_;
std::ofstream DisjointSetBenchmark::weight_union_statistics_;
std::ofstream DisjointSetBenchmark::weight_union_FC_statistics_;
std::ofstream DisjointSetBenchmark::weight_union_PS_statistics_;
std::ofstream DisjointSetBenchmark::weight_union_PH_statistics_;
std::ofstream DisjointSetBenchmark::rank_union_statistics_;
std::ofstream DisjointSetBenchmark::rank_union_FC_statistics_;
std::ofstream DisjointSetBenchmark::rank_union_PS_statistics_;
std::ofstream DisjointSetBenchmark::rank_union_PH_statistics_;

TEST_F(DisjointSetBenchmark, QuickUnion) {
  RunBenchmark<disjoint_set::QuickUnion<uint64_t>>(quick_union_statistics_);
}

TEST_F(DisjointSetBenchmark, QuickUnionFC) {
  RunBenchmark<disjoint_set::QuickUnionFullCompression<uint64_t>>(
      quick_union_FC_statistics_, true);
}

TEST_F(DisjointSetBenchmark, QuickUnionPS) {
  RunBenchmark<disjoint_set::QuickUnionPathSplitting<uint64_t>>(
      quick_union_PS_statistics_);
}

TEST_F(DisjointSetBenchmark, QuickUnionPH) {
  RunBenchmark<disjoint_set::QuickUnionPathHalving<uint64_t>>(
      quick_union_PH_statistics_);
}

TEST_F(DisjointSetBenchmark, WeightUnion) {
  RunBenchmark<disjoint_set::WeightUnion<int16_t>>(weight_union_statistics_);
}

TEST_F(DisjointSetBenchmark, WeightUnionFC) {
  RunBenchmark<disjoint_set::WeightUnionFullCompression<int64_t>>(
      weight_union_FC_statistics_, true);
}

TEST_F(DisjointSetBenchmark, WeightUnionPS) {
  RunBenchmark<disjoint_set::WeightUnionPathSplitting<int64_t>>(
      weight_union_PS_statistics_);
}

TEST_F(DisjointSetBenchmark, WeightUnionPH) {
  RunBenchmark<disjoint_set::WeightUnionPathHalving<int64_t>>(
      weight_union_PH_statistics_);
}

TEST_F(DisjointSetBenchmark, RankUnion) {
  RunBenchmark<disjoint_set::RankUnion<int64_t>>(rank_union_statistics_);
}

TEST_F(DisjointSetBenchmark, RankUnionFC) {
  RunBenchmark<disjoint_set::RankUnionFullCompression<int64_t>>(
      rank_union_FC_statistics_, true);
}

TEST_F(DisjointSetBenchmark, RankUnionPS) {
  RunBenchmark<disjoint_set::RankUnionPathSplitting<int64_t>>(
      rank_union_PS_statistics_);
}

TEST_F(DisjointSetBenchmark, RankUnionPH) {
  RunBenchmark<disjoint_set::RankUnionPathHalving<int64_t>>(
      rank_union_PH_statistics_);
}
#endif
}  // namespace disjoint_set_benchmark