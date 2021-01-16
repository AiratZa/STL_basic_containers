cmake_minimum_required(VERSION 3.17)
project(ft_containers)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(google_tests/lib)
include_directories(google_tests/lib/googletest/include)

set(SOURCE_FILES tests/test_list/test_list_push_back.cpp source/list.hpp source/iterators.hpp  tests/test_list/test_list_push_front.cpp tests/test_list/test_list_siize.cpp tests/test_list/test_list.hpp tests/test_list/test_list_begin.cpp tests/test_list/test_list_end.cpp tests/test_list/test_list_rbegin.cpp source/allocator_trairs_wrapper.hpp tests/test_list/tests_list_empty_clear_max_size.cpp tests/test_list/tests_list_front_back.cpp tests/test_list/test_list_insert.cpp tests/test_list/test_list_resize.cpp tests/test_list/test_list_erase.cpp tests/test_list/test_list_splice.cpp)
add_executable(ft_containers ${SOURCE_FILES})
target_link_libraries(ft_containers gtest gtest_main)

