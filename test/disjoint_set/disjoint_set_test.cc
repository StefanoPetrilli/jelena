#include "disjoint_set_test.h"
#include "disjoint_set.h"

namespace disjoint_set_test {
TEST_F(DisjointSetTest, AfterInstantiation_Expect_AllBlocksInADifferentSet) {
  EXPECT_EQ(disjoint_set_.Find((uint16_t)10), (uint16_t)10);
}

}  // namespace disjoint_set_test