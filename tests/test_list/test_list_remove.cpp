//
// Created by airat on 16.01.2021.
//

#include "test_list.hpp"

TEST(List_remove, remove_0_elements) {
    ft::list<int> l1(0);
    std::list<int> l2(0);

    l1.remove(0);
    l2.remove(0);
    ASSERT_LISTS_EQ(l1, l2);
}


TEST(List_remove, remove_few_elements) {
    ft::list<int> l1(100, 256);
    std::list<int> l2(100, 256);

    l1.push_back(7);
    l2.push_back(7);

    ASSERT_LISTS_EQ(l1, l2);

    l1.remove(0);
    l2.remove(0);
    ASSERT_LISTS_EQ(l1, l2);

    l1.remove(7);
    l2.remove(7);
    ASSERT_LISTS_EQ(l1, l2);

    l1.remove(256);
    l2.remove(256);
    ASSERT_LISTS_EQ(l1, l2);

}

