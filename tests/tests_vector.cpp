//
// Created by airat on 09.01.2021.
//

#include <list>
#include "../source/list.hpp"

#include <gtest/gtest.h>


TEST(Vector, push_back) {
    ft::list<int> l1;
    std::list<int> l2;

    ASSERT_EQ(l1.size(), l2.size());
    l1.push_back(1);
    l2.push_back(1);
    ASSERT_EQ(l1.size(), l2.size());
}

TEST(Vector, push_front) {
    ft::list<int> l1;
    std::list<int> l2;

    ASSERT_EQ(l1.size(), l2.size());
    l1.push_front(1);
    l2.push_front(1);
    ASSERT_EQ(l1.size(), l2.size());
}

