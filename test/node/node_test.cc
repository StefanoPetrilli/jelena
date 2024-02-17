#include "node.h"
#include "node_test.h"

namespace node_test {
TEST_F(NodeTest, NoNeighborsNode_HasNext_ReturnsFalse) {
  EXPECT_FALSE(no_neighbors_node_.HasNext());
}

TEST_F(NodeTest, NoNeighborsNode_HasPrevious_ReturnsFalse) {
  EXPECT_FALSE(no_neighbors_node_.HasPrevious());
}

TEST_F(NodeTest, NoNeighborsNodeAfter_SetNext_HasNextReturnsTrue) {
  auto ptr = std::make_shared<node::Node<int>>(5);
  no_neighbors_node_.SetNext(ptr);
  EXPECT_TRUE(no_neighbors_node_.HasNext());
}

TEST_F(NodeTest, NoNeighborsNodeAfter_SetPrevious_HasPreviousReturnsTrue) {
  auto ptr = std::make_shared<node::Node<int>>(5);
  no_neighbors_node_.SetPrevious(ptr);
  EXPECT_TRUE(no_neighbors_node_.HasPrevious());
}

TEST_F(NodeTest,
       NoNeighborsNodeAfterSetNext_GetNext_ReturnsExpectedValue) {
  auto ptr = std::make_shared<node::Node<int>>(5);
  no_neighbors_node_.SetNext(ptr);
  EXPECT_EQ(no_neighbors_node_.GetNextNode(), ptr);
}

TEST_F(NodeTest,
       NoNeighborsNodeAfterSetPrevious_GetPrevious_ReturnsExpectedValue) {
  auto ptr = std::make_shared<node::Node<int>>(5);
  no_neighbors_node_.SetPrevious(ptr);
  EXPECT_EQ(no_neighbors_node_.GetPreviousNode(), ptr);
}
}  // namespace node_test