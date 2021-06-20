//
// Created by airat on 09.01.2021.
//
#include "test_list.hpp"

TEST(List_begin, begin_1_element) {
    ft::list<int> l1(0);
    std::list<int> l2(0);

    l1.push_back(1);
    l2.push_back(1);
    ASSERT_EQ(*l1.begin(), *l2.begin());
}

TEST(List_begin, more_elemets) {
    ft::list<int> l1(100);
    std::list<int> l2(100);

    ft::list<int>::iterator it1 = l1.begin();
    std::list<int>::iterator it2 = l2.begin();
    ASSERT_EQ(*it1, *it2);

    for (int i = 0; i < 100; i++) {
        ASSERT_EQ(*it1, *it2);
        ++it1;
        ++it2;
    }
}

TEST(List_begin, const_begin_1_element) {
    const ft::list<int> l1(1);
    std::list<int> l2(1);

    ASSERT_EQ(*l1.begin(), *l2.begin());
}

TEST(List_begin, const_more_elemets) {
    const ft::list<int> l1(100);
    const std::list<int> l2(100);

    ASSERT_EQ(*l1.begin(), *l2.begin());
}


// RBEGIN



TEST(List_rbegin, rbegin_1_element) {
    ft::list<int> l1(0);
    std::list<int> l2(0);

    l1.push_back(1);
    l2.push_back(1);
    ASSERT_EQ(*l1.rbegin(), *l2.rbegin());
}

TEST(List_rbegin, more_elemets) {
    ft::list<int> l1(100);
    std::list<int> l2(100);

    ASSERT_EQ(*l1.rbegin(), *l2.rbegin());
}


TEST(List_rbegin, const_rbegin_1_element) {
    const ft::list<int> l1(1);
    std::list<int> l2(1);

    ASSERT_EQ(*l1.rbegin(), *l2.rbegin());
}

TEST(List_rbegin, const_more_elemets) {
    const ft::list<int> l1(100);
    const std::list<int> l2(100);

    ASSERT_EQ(*l1.rbegin(), *l2.rbegin());
}

