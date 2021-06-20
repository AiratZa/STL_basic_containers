//
// Created by airat on 16.01.2021.
//

// FOR TESTS

//#include <gtest/gtest.h>
//
// int main(int argc, char* argv[]) {
//    testing::InitGoogleTest(&argc, argv);
//    return RUN_ALL_TESTS();
//}

// FOR COMPILATION CHECK
//  clang++ main.cpp -std=c++98  -Wall -Wextra -Werror
#include "source/list.hpp"
#include "source/map.hpp"
#include "source/queue.hpp"
#include "source/stack.hpp"
#include "source/vector.hpp"


int main(void)
{
    ft::vector<int> vector;
    ft::list<int> list;
    ft::map<int, int> map;
    ft::queue<int> queue;
    ft::stack<int> stack;
    return 0;
}