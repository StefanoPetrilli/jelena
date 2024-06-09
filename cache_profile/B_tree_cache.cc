#include <fstream>
#include <iostream>
#include <random>
#include "b_tree.h"

#define SEED 42
const uint32_t kSize_ = 100000;
const uint32_t kInsertCount = 20000;

std::vector<uint32_t> GetNumberList() {
  std::vector<uint32_t> vec(kSize_);
  for (uint32_t i = 0; i < kSize_; ++i) {
    vec[i] = i;
  }
  return vec;
}

void BInsertValues(tree::BTree<uint32_t>& b_tree,
                   const std::vector<uint32_t>& input, uint32_t size) {
  for (size_t i = 0; i < size; i++)
    b_tree.Insert(input.at(i));
  return;
}

void BContainsValues(tree::BTree<uint32_t>& b_tree,
                     const std::vector<uint32_t>& input, uint32_t size) {
  for (size_t i = 0; i < size; i++) {
    b_tree.Contains(input.at(i));
  }
  return;
}

void BMixedInsertContain(tree::BTree<uint32_t>& b_tree,
                         const std::vector<uint32_t>& input, uint32_t size) {
  size_t i;
  for (i = 0; i < size; i++)
    b_tree.Insert(input.at(i));
  for (i = 0; i < size; i++)
    b_tree.Contains(input.at(i));
  for (; i < size + size; i++)
    b_tree.Insert(input.at(i));
  for (i = size / 2; i < size * 3; i++)
    b_tree.Contains(input.at(i));
  return;
}

int main() {
  std::mt19937 rng = std::mt19937(SEED);
  auto input = GetNumberList();
  std::shuffle(input.begin(), input.end(), rng);
  auto b_tree = tree::BTree<uint32_t, uint16_t>(5);

  for (size_t i = 0; i < 25; i++) {
    BInsertValues(b_tree, input, kInsertCount);

    BContainsValues(b_tree, input, kInsertCount);

    std::shuffle(input.begin(), input.end(), rng);
    b_tree.Erase();
  }

  // 60% Contains  40% Insert
  for (size_t i = 0; i < 25; i++) {
    BMixedInsertContain(b_tree, input, kInsertCount);

    std::shuffle(input.begin(), input.end(), rng);
    b_tree.Erase();
  }

  return 0;
}