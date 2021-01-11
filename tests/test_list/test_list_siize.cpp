//
// Created by airat on 09.01.2021.
//

#include "test_list.hpp"

TEST(List_size, zero_size) {
    ft::list<int> l1(0);
    std::list<int> l2(0);

    ASSERT_EQ(l1.size(), l2.size());
}

TEST(List_size, preinitialized_values) {
    ft::list<int> l1(100, 100);
    std::list<int> l2(100, 100);

    ASSERT_EQ(l1.size(), l2.size());
}

TEST(List_size, default_values) {
    ft::list<int> l1(100);
    std::list<int> l2(100);

    ASSERT_EQ(l1.size(), l2.size());
}
