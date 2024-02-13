#include "node.h"
#include "node_test.h"

namespace node_test {
TEST_F(NodeTest, True) {
  EXPECT_EQ(true, true);
}
}  // namespace node_test