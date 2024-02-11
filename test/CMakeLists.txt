# add_subdirectory(infrastructure)

add_executable(jelena_tests main_test.cc)

target_link_libraries(jelena_tests PUBLIC GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(jelena_tests)
