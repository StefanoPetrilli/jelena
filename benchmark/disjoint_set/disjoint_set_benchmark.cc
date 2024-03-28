#include "disjoint_set_benchmark.h"

namespace disjoint_set_benchmark {
std::ofstream DisjointSetBenchmark::quick_union_statistics_;
std::ofstream DisjointSetBenchmark::weight_quick_union_statistics_;
std::ofstream DisjointSetBenchmark::rank_quick_union_statistics_;

TEST_F(DisjointSetBenchmark, QuickUnion) {
  RunBenchmark<disjoint_set::QuickUnion<uint16_t>>(quick_union_statistics_);
}

TEST_F(DisjointSetBenchmark, WeightQuickUnion) {
  RunBenchmark<disjoint_set::WeightQuickUnion<int16_t>>(weight_quick_union_statistics_);
}

TEST_F(DisjointSetBenchmark, RankQuickUnion) {
  RunBenchmark<disjoint_set::RankQuickUnion<int16_t>>(rank_quick_union_statistics_);
}

}  // namespace disjoint_set_benchmark