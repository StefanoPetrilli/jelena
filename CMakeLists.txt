cmake_minimum_required(VERSION 3.22)
project(jelena)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(FETCHCONTENT_QUIET off)
set(CMAKE_EXE_LINKER_FLAGS
    "${CMAKE_EXE_LINKER_FLAGS} -Wl,--whole-archive -Wl,--no-whole-archive")
add_compile_options(-Wall -Wextra -Wpedantic)

option(DISJOINT_SET_BENCHMARK "Execute the benchmarks for disjoint set" OFF)
option(BTREE_BENCHMARK "Execute the benchmarks for B-Tree" ON)

if(DISJOINT_SET_BENCHMARK)
  message(STATUS "Compiling benchmarks for disjoint set")
  add_definitions(-DDISJOINT_SET_BENCHMARK)
endif()

if(BTREE_BENCHMARK)
  message(STATUS "Compiling benchmarks for B-Tree")
  add_definitions(-DBTREE_BENCHMARK)
endif()

# Include google test
include(FetchContent)
include(GoogleTest)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt
    ON
    CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
enable_testing()

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(benchmark)
