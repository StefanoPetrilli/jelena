add_executable(
  jelena_tests
  main_test.cc
  node/node_test.cc
  node/node_test.h
  linked_list/linked_list_test.cc
  linked_list/linked_list_test.h
  tree/binary_tree_test.cc
  tree/binary_tree_test.h
  disjoint_set/disjoint_set_test.cc
  disjoint_set/disjoint_set_test.h
  disjoint_set/weighted_quick_union_test.h)

target_link_libraries(jelena_tests PUBLIC GTest::gtest_main node linked_list
                                          tree disjoint_set)

include(GoogleTest)
gtest_discover_tests(jelena_tests)
