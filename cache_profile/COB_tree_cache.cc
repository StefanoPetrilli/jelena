#include <fstream>
#include <iostream>
#include <random>
#include "cob_tree.h"

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

void COBInsertValues(tree::COBTree<uint32_t>& cob_tree,
                     const std::vector<uint32_t>& input, uint32_t size) {
  for (size_t i = 0; i < size; i++)
    cob_tree.Insert(input.at(i));
  return;
}

void COBContainsValues(tree::COBTree<uint32_t>& cob_tree,
                       const std::vector<uint32_t>& input, uint32_t size) {
  for (size_t i = 0; i < size; i++) {
    cob_tree.Contains(input.at(i));
  }
  return;
}

void COBMixedInsertContain(tree::COBTree<uint32_t>& cob_tree,
                           const std::vector<uint32_t>& input, uint32_t size) {
  size_t i;
  for (i = 0; i < size; i++)
    cob_tree.Insert(input.at(i));
  for (i = 0; i < size; i++)
    cob_tree.Contains(input.at(i));
  for (; i < size + size; i++)
    cob_tree.Insert(input.at(i));
  for (i = size / 2; i < size * 3; i++)
    cob_tree.Contains(input.at(i));
  return;
}

int main() {
  std::mt19937 rng = std::mt19937(SEED);
  auto input = GetNumberList();
  std::shuffle(input.begin(), input.end(), rng);
  auto cob_tree = tree::COBTree<uint32_t>();

  for (size_t i = 0; i < 25; i++) {
    COBInsertValues(cob_tree, input, kInsertCount);

    COBContainsValues(cob_tree, input, kInsertCount);

    std::shuffle(input.begin(), input.end(), rng);
    cob_tree.Erase();
  }

  // 60% Contains  40% Insert
  for (size_t i = 0; i < 25; i++) {
    COBMixedInsertContain(cob_tree, input, kInsertCount);

    std::shuffle(input.begin(), input.end(), rng);
    cob_tree.Erase();
  }
  return 0;
}