//
// Created by airat on 17.01.2021.
//

#ifndef FT_CONTAINERS_TEST_QUEUE_HPP
#define FT_CONTAINERS_TEST_QUEUE_HPP

#include <queue>
#include <list>
#include "../../source/queue.hpp"

#include "../test_list/test_list.hpp"
#include <gtest/gtest.h>

template <typename T>
void ASSERT_QUEUES_EQ(ft::queue<T>& s1, std::queue<T, std::list<T> >& s2) {

    ASSERT_EQ(s1.size(), s2.size());
    ASSERT_EQ(s1.empty(), s2.empty());
    ASSERT_EQ(s1.front(), s2.front());
    ASSERT_EQ(s1.back(), s2.back());

    ft::list<T> tmp1;
    std::list<T> tmp2;

    while (s1.size()) {
        tmp1.push_back(s1.front());
        s1.pop();
    }

    while (s2.size()) {
        tmp2.push_back(s2.front());
        s2.pop();
    }

    ASSERT_LISTS_EQ(tmp1, tmp2);

    while (tmp1.size()) {
        s1.push(tmp1.front());
        tmp1.pop_front();
    }

    while (tmp2.size()) {
        s2.push(tmp2.front());
        tmp2.pop_front();
    }

}

#endif //FT_CONTAINERS_TEST_QUEUE_HPP
