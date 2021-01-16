//
// Created by airat on 16.01.2021.
//

#include "test_list.hpp"

TEST(List_pop_front, pop_front) {
    ft::list<int> l1(0);
    std::list<int> l2(0);

    for (int i=1; i <= 5; ++i) {
        l1.push_front(i);
        l2.push_front(i);
    }

    ASSERT_EQ(l1.size(), l2.size());

    while ( (l1.begin() != l1.end()) || (l2.begin() != l2.end()) ) {
        l1.pop_front();
        l2.pop_front();
    }
    ASSERT_EQ(l1.size(), l2.size());
}

TEST(List_pop_back, pop_back) {
    ft::list<int> l1(0);
    std::list<int> l2(0);

    for (int i=1; i <= 5; ++i) {
        l1.push_back(i);
        l2.push_back(i);
    }

    ASSERT_EQ(l1.size(), l2.size());

    while ( (l1.begin() != l1.end()) || (l2.begin() != l2.end()) ) {
        l1.pop_back();
        l2.pop_back();
    }
    ASSERT_EQ(l1.size(), l2.size());
}



