add_executable(
  jelena_tests
  main_test.cc
  node/node_test.cc
  node/node_test.h
  linked_list/linked_list_test.cc
  linked_list/linked_list_test.h
  tree/binary_tree_test.cc
  tree/binary_tree_test.h
  tree/b_tree_test.h
  tree/b_tree_test.cc
  disjoint_set/quick_union_test.cc
  disjoint_set/quick_union_test.h
  disjoint_set/rank_union_test.cc
  disjoint_set/rank_union_test.h
  disjoint_set/weighted_union_test.cc
  disjoint_set/weighted_union_test.h
  kd_tree/kd_tree_test.cc
  kd_tree/kd_tree_test.h
)

target_link_libraries(jelena_tests PUBLIC GTest::gtest_main node linked_list
                                          tree disjoint_set kd_tree)

include(GoogleTest)
gtest_discover_tests(jelena_tests)
