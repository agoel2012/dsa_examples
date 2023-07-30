cmake_minimum_required(VERSION 3.16)

project(TreeExamples)

include_directories(include)
add_executable(LCA lowest_common_ancestor.cpp)
target_compile_options(LCA PRIVATE -g -O3 -Werror -Wall)
add_executable(AVL avl_tree.cpp)
target_compile_options(AVL PRIVATE -g -O3 -Werror -Wall)
add_executable(IntervalTree interval_tree.cpp)
target_compile_options(IntervalTree PRIVATE -g -O3 -Werror -Wall)
