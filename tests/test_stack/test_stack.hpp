//
// Created by airat on 17.01.2021.
//

#ifndef FT_CONTAINERS_TEST_STACK_HPP
#define FT_CONTAINERS_TEST_STACK_HPP

#include <stack>
#include <list>
#include "../../source/stack.hpp"

#include "../test_list/test_list.hpp"
#include <gtest/gtest.h>

template <typename T>
void ASSERT_STACKS_EQ(ft::stack<T>& s1, std::stack<T, std::list<T> >& s2) {

    ASSERT_EQ(s1.size(), s2.size());
    ASSERT_EQ(s1.empty(), s2.empty());
    ASSERT_EQ(s1.top(), s2.top());

    ft::list<T> tmp1;
    std::list<T> tmp2;

    while (s1.size()) {
        tmp1.push_back(s1.top());
        s1.pop();
    }

    while (s2.size()) {
        tmp2.push_back(s2.top());
        s2.pop();
    }

    ASSERT_LISTS_EQ(tmp1, tmp2);

    while (tmp1.size()) {
        s1.push(tmp1.back());
        tmp1.pop_back();
    }

    while (tmp2.size()) {
        s2.push(tmp2.back());
        tmp2.pop_back();
    }

}


#endif //FT_CONTAINERS_TEST_STACK_HPP
