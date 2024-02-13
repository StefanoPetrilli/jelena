add_executable(
  jelena_tests main_test.cc node/node_test.cc node/node_test.h
               linked_list/linked_list_test.cc linked_list/linked_list_test.h)

target_link_libraries(jelena_tests PUBLIC GTest::gtest_main node linked_list)

include(GoogleTest)
gtest_discover_tests(jelena_tests)
