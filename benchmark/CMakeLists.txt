add_executable(
  jelena_benchmark
  main_benchmark.cc
  disjoint_set/disjoint_set_benchmark.h
  disjoint_set/disjoint_set_benchmark.cc
  disjoint_set/statistics.h
  tree/b_tree_benchmark.h
  tree/b_tree_benchmark.cc
  tree/cob_tree_benchmark.h
  tree/cob_tree_benchmark.cc
)

target_link_libraries(jelena_benchmark PUBLIC GTest::gtest_main disjoint_set
                        tree)

include(GoogleTest)
gtest_discover_tests(jelena_benchmark)
