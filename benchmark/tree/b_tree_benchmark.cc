#include "b_tree_benchmark.h"
#include "b_tree.h"

namespace b_tree_benchmark {
#ifdef BTREE_BENCHMARK

TEST_F(BTreeBenchmark, ReplicateTable5) {
  std::array<uint32_t, 4> sizes = {1000, 10000, 100000, 1000000};
  std::array<uint32_t, 4> orders = {5, 20, 200, 400};

  for (auto order : orders) {
    uint32_t height = 0;
    table_5_replication_ << order << " | ";

    for (auto size : sizes) {
      for (uint16_t i = 0; i < kNumberExecition_; i++) {
        auto b_tree = tree::BTree<uint32_t>(order);
        std::shuffle(keys_.begin(), keys_.end(), rng_);
        for (uint32_t i = 0; i < size; i++) {
          b_tree.Insert(keys_[i]);
        }
        height += b_tree.GetHeight();
      }
      table_5_replication_ << static_cast<double>(height) / kNumberExecition_
                           << " | ";
      height = 0;
    }
    table_5_replication_ << std::endl;
  }
}
#endif
}  // namespace b_tree_benchmark