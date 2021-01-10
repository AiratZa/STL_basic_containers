cmake_minimum_required(VERSION 3.17)
project(ft_containers)

set(CMAKE_CXX_STANDARD 98)

add_subdirectory(google_tests/lib)
include_directories(google_tests/lib/googletest/include)

set(SOURCE_FILES tests/test_list/test_list_push_back.cpp source/list.hpp source/iterators.hpp  tests/test_list/test_list_push_front.cpp tests/test_list/test_list_siize.cpp tests/test_list/test_list.hpp tests/test_list/test_list_begin.cpp tests/test_list/test_list_end.cpp tests/test_list/test_list_rbegin.cpp)
add_executable(ft_containers ${SOURCE_FILES})
target_link_libraries(ft_containers gtest gtest_main)
