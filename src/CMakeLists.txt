add_subdirectory(linked_list)

add_executable(jelena main.cc)

target_link_libraries(jelena PUBLIC linked_list)
