add_executable(
  cob_tree_cache
  COB_tree_cache.cc
)

add_executable(
  b_tree_cache
  B_tree_cache.cc
)

target_link_libraries(cob_tree_cache PUBLIC tree)
target_link_libraries(b_tree_cache PUBLIC tree)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/run_COB_profiling.sh ${CMAKE_CURRENT_BINARY_DIR}/run_COB_profiling.sh COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/run_B_profiling.sh ${CMAKE_CURRENT_BINARY_DIR}/run_B_profiling.sh COPYONLY)
