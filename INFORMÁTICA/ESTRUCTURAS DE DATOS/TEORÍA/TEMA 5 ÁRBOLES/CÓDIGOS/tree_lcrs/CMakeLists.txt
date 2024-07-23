cmake_minimum_required(VERSION 3.16)
project(tree)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")

include_directories(include)

add_executable(1_tree_manipulation
  src/1_tree_manipulation.cpp)

add_executable(2_tree_recursion
  src/2_tree_recursion.cpp)

add_executable(3_tree_iteration
  src/3_tree_iteration.cpp)

add_executable(4_tree_ordered_insertion
  src/4_tree_ordered_insertion.cpp)

add_executable(5_tree_dictionary
  src/5_tree_dictionary.cpp)
