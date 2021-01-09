//
// Created by airat on 09.01.2021.
//
#include "test_list.hpp"
#include <iostream>


TEST(List_begin, push_back_1) {
    ft::list<int> l1;
    std::list<int> l2;

    l1.push_back(1);
    l2.push_back(1);
    ASSERT_EQ(*l1.begin(), *l2.begin());
}