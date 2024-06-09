#include "b_tree_benchmark.h"
#include "b_tree.h"

namespace b_tree_benchmark {
#ifdef BTREE_BENCHMARK

TEST_F(BTreeBenchmark, ReplicateTable5) {
  this->table_5_replication_ << "order | ";
  std::array<uint32_t, 4> sizes = {1000, 10000, 100000, 1000000};
  for (auto size : sizes) {
    table_5_replication_ << size << " | ";
  }
  table_5_replication_ << std::endl;
  std::array<uint32_t, 4> orders = {5, 20, 200, 400};

  for (auto order : orders) {
    uint32_t height = 0;
    table_5_replication_ << order << " | ";

    for (auto size : sizes) {
      for (uint16_t i = 0; i < kNumberExecition_; i++) {
        auto b_tree = tree::BTree<uint32_t>(order);
        for (uint32_t i = 0; i < size; i++) {
          b_tree.Insert(dist_(rng_));
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

TEST_F(BTreeBenchmark, ReplicateTable5Unbalanced) {
  table_5_replication_unbalanced << "order | ";
  std::array<uint32_t, 4> sizes = {1000, 10000, 100000, 1000000};
  for (auto size : sizes) {
    table_5_replication_unbalanced << size << " | ";
  }
  table_5_replication_unbalanced << std::endl;
  std::array<uint32_t, 4> orders = {5, 20, 200, 400};

  for (auto order : orders) {
    uint32_t height = 0;
    table_5_replication_unbalanced << order << " | ";

    for (auto size : sizes) {
      for (uint16_t i = 0; i < kNumberExecition_; i++) {
        auto b_tree = tree::BTree<uint32_t>(order);
        for (uint32_t i = 0; i < size; i++) {
          b_tree.Insert(i);
        }
        height += b_tree.GetHeight();
      }
      table_5_replication_unbalanced << static_cast<double>(height) / kNumberExecition_
                           << " | ";
      height = 0;
    }
    table_5_replication_unbalanced << std::endl;
  }
}

TEST_F(BTreeBenchmark, UnbalancedSplitProbability) {
  split_count_unbalanced_ << "order | ";
  std::array<uint32_t, 3> sizes = {1000, 10000, 1000000};
  for (auto size : sizes) {
    split_count_unbalanced_ << size << " | ";
  }
  split_count_unbalanced_ << std::endl;
  std::array<uint32_t, 4> orders = {5, 20, 200, 400};

  for (auto order : orders) {
    uint32_t split_count = 0;
    split_count_unbalanced_ << order << " | ";

    for (auto size : sizes) {
      for (uint16_t i = 0; i < kNumberExecition_; i++) {
        auto b_tree = tree::BTree<uint32_t>(order);
        for (uint32_t i = 0; i < size; i++) {
          b_tree.Insert(i);
        }
        split_count += b_tree.GetSplitCount();
      }
      split_count_unbalanced_ << static_cast<double>(split_count) / kNumberExecition_ / size
                           << " | ";
      split_count = 0;
    }
    split_count_unbalanced_ << std::endl;
  }
}

TEST_F(BTreeBenchmark, SplitProbability) {
  split_count_ << "order | ";
  std::array<uint32_t, 3> sizes = {1000, 10000, 1000000};
  for (auto size : sizes) {
    split_count_ << size << " | ";
  }
  split_count_ << std::endl;
  std::array<uint32_t, 4> orders = {5, 20, 200, 400};

  for (auto order : orders) {
    uint32_t split_count = 0;
    split_count_ << order << " | ";

    for (auto size : sizes) {
      for (uint16_t i = 0; i < kNumberExecition_; i++) {
        auto b_tree = tree::BTree<uint32_t>(order);
        for (uint32_t i = 0; i < size; i++) {
          b_tree.Insert(dist_(rng_));
        }
        split_count += b_tree.GetSplitCount();
      }
      split_count_ << static_cast<double>(split_count) / kNumberExecition_ / size
                           << " | ";
      split_count = 0;
    }
    split_count_ << std::endl;
  }
}
#endif
}  // namespace b_tree_benchmark