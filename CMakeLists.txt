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
        source/allocator_traits_wrapper.hpp
        tests/test_list/test_list_assign.cpp)

file(GLOB TEST_LIST_SRC "tests/test_list/*.hpp" "tests/test_list/*.cpp")

add_executable(ft_containers ${SOURCE_FILES} ${TEST_LIST_SRC} )
target_link_libraries(ft_containers gtest ) #gtest_main


