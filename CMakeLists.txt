cmake_minimum_required(VERSION 3.17)
project(ft_containers)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(google_test/)
include_directories(google_test/googletest/include)

set(SOURCE_FILES
        main.cpp
        source/list.hpp
        source/allocator_trairs_wrapper.hpp
        )

file(GLOB TEST_LIST_SRC "tests/test_list/*.hpp" "tests/test_list/*.cpp")
#set(TEST_LIST tests/test_list/*.cpp tests/test_list/*.hpp)

add_executable(ft_containers ${SOURCE_FILES} ${TEST_LIST_SRC} )
target_link_libraries(ft_containers gtest ) #gtest_main

#tests/test_list/test_list_push_back.cpp

#source/iterators.hpp
#tests/test_list/test_list_push_front.cpp
#tests/test_list/test_list_siize.cpp
#tests/test_list/test_list.hpp
#tests/test_list/test_list_begin.cpp
#tests/test_list/test_list_end.cpp
#tests/test_list/test_list_rbegin.cpp
#
#tests/test_list/tests_list_empty_clear_max_size.cpp
#tests/test_list/tests_list_front_back.cpp
#tests/test_list/test_list_insert.cpp
#tests/test_list/test_list_resize.cpp
#tests/test_list/test_list_erase.cpp
#tests/test_list/test_list_splice.cpp

