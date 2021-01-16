//
// Created by airat on 16.01.2021.
//

#include "test_list.hpp"

// list member function
TEST(List_swap, swap_member_func_zero_elems) {
    ft::list<int> l1(0);
    std::list<int> l2(0);

    ft::list<int> l1_2(0);
    std::list<int> l2_2(0);

    ASSERT_LISTS_EQ(l1, l2);
    ASSERT_LISTS_EQ(l1_2, l2_2);

    l1.swap(l1_2);
    l2.swap(l2_2);

    ASSERT_LISTS_EQ(l1, l2);
    ASSERT_LISTS_EQ(l1_2, l2_2);

}

TEST(List_swap, swap_member_func_non_empty) {
    ft::list<int> l1(100, 852);
    std::list<int> l2(100, 852);

    ft::list<int> l1_2(951, 563);
    std::list<int> l2_2(951, 563);

    ASSERT_LISTS_EQ(l1, l2);
    ASSERT_LISTS_EQ(l1_2, l2_2);

    l1.swap(l1_2);
    l2.swap(l2_2);

    ASSERT_LISTS_EQ(l1, l2);
    ASSERT_LISTS_EQ(l1_2, l2_2);

}

// Non-member function

TEST(List_swap, swap_non_member_func_zero_elems) {
    ft::list<int> l1(0);
    std::list<int> l2(0);

    ft::list<int> l1_2(0);
    std::list<int> l2_2(0);

    ASSERT_LISTS_EQ(l1, l2);
    ASSERT_LISTS_EQ(l1_2, l2_2);

    ft::swap(l1, l1_2);
    std::swap(l2, l2_2);

    ASSERT_LISTS_EQ(l1, l2);
    ASSERT_LISTS_EQ(l1_2, l2_2);

}

TEST(List_swap, swap_non_member_func_non_empty) {
    ft::list<int> l1(100, 852);
    std::list<int> l2(100, 852);

    ft::list<int> l1_2(951, 563);
    std::list<int> l2_2(951, 563);

    ASSERT_LISTS_EQ(l1, l2);
    ASSERT_LISTS_EQ(l1_2, l2_2);

    ft::swap(l1, l1_2);
    std::swap(l2, l2_2);

    ASSERT_LISTS_EQ(l1, l2);
    ASSERT_LISTS_EQ(l1_2, l2_2);

}




