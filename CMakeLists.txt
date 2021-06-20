cmake_minimum_required(VERSION 3.17)
project(ft_containers)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_CXX_EXTENSIONS OFF)


add_subdirectory(google_test/)
include_directories(google_test/googletest/include)

set(SOURCE_FILES
        main.cpp
        source/details/allocator_traits_wrapper.hpp
        source/details/red_black_tree.hpp
        source/list.hpp
        source/stack.hpp
        source/queue.hpp
        source/vector.hpp
        source/map.hpp source/details/meta_programming.hpp
        source/details/iterator.hpp
        source/details/base_algorithms.hpp
        tests/test_map/test_map.hpp
        tests/test_map/test_map.cpp
        source/details/red_black_tree_utils.hpp
        source/details/red_black_tree_iterators.hpp
        source/details/red_black_tree_parts.hpp
        )

file(GLOB TEST_LIST_SRC "tests/test_list/*.hpp" "tests/test_list/*.cpp")
file(GLOB TEST_STACK_SRC "tests/test_stack/*.hpp" "tests/test_stack/*.cpp")
file(GLOB TEST_QUEUE_SRC "tests/test_queue/*.hpp" "tests/test_queue/*.cpp")
file(GLOB TEST_VECTOR_SRC "tests/test_vector/*.hpp" "tests/test_vector/*.cpp")

set (TEST_FILES ${TEST_LIST_SRC} ${TEST_STACK_SRC} ${TEST_QUEUE_SRC} ${TEST_VECTOR_SRC} tests/test_list/test_list.cpp)

set_source_files_properties(${SOURCE_FILES} ${TEST_FILES} PROPERTIES COMPILE_FLAGS -Wall -Wextra -Werror)

add_executable(ft_containers ${SOURCE_FILES} ${TEST_FILES} )
target_link_libraries(ft_containers gtest )


