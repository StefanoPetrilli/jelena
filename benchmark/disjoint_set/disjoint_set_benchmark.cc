#include "disjoint_set_benchmark.h"

namespace disjoint_set_benchmark {
std::ofstream DisjointSetBenchmark::quick_union_statistics_;
std::ofstream DisjointSetBenchmark::weight_union_statistics_;
std::ofstream DisjointSetBenchmark::rank_union_statistics_;

TEST_F(DisjointSetBenchmark, QuickUnion) {
  RunBenchmark<disjoint_set::QuickUnion<uint16_t>>(quick_union_statistics_);
}

TEST_F(DisjointSetBenchmark, WeightUnion) {
  RunBenchmark<disjoint_set::WeightUnion<int16_t>>(weight_union_statistics_);
}

TEST_F(DisjointSetBenchmark, RankUnion) {
  RunBenchmark<disjoint_set::RankUnion<int16_t>>(rank_union_statistics_);
}

}  // namespace disjoint_set_benchmark