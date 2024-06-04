#include "cob_tree_benchmark.h"
#include "cob_tree.h"

namespace cob_tree_benchmark {
#ifdef COBTREE_BENCHMARK

TEST_F(COBTreeBenchmark, big) {
  auto cob_tree = tree::COBTree<uint32_t>();
  for (uint32_t i = 1; i < 500000; i++) {
    if (i % 10000 == 0) {
      std::cout << i << std::endl;
    }

    cob_tree.Insert(i);
  }

  SUCCEED();
}
#endif
}  // namespace cob_tree_benchmark