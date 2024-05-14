add_subdirectory(array)
add_subdirectory(node)
add_subdirectory(linked_list)
add_subdirectory(tree)
add_subdirectory(kd_tree)
add_subdirectory(disjoint_set)

add_executable(jelena main.cc)

target_link_libraries(jelena PUBLIC node linked_list tree disjoint_set kd_tree
                                    array)
