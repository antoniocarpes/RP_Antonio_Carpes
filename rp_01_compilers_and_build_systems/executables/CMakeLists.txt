message("-------------CMake executable ---------------------")

# TODO: compile executable that will be run
add_executable(${PROJECT_NAME} many_object_in_stack_example.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE "{CMAKE_SOURCE_DIR}/src")

# TODO: link the executable against the core_library

target_link_libraries(${PROJECT_NAME} core_library)

message("----------Executable built -----------------")

