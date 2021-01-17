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
        source/stack.hpp)

file(GLOB TEST_LIST_SRC "tests/test_list/*.hpp" "tests/test_list/*.cpp")
file(GLOB TEST_STACK_SRC "tests/test_stack/*.hpp" "tests/test_stack/*.cpp")

set_source_files_properties(${SOURCE_FILES} ${TEST_LIST_SRC} ${TEST_STACK_SRC} PROPERTIES COMPILE_FLAGS -Wall -Wextra -Werror)

add_executable(ft_containers ${SOURCE_FILES} ${TEST_LIST_SRC} ${TEST_STACK_SRC} )
target_link_libraries(ft_containers gtest )


