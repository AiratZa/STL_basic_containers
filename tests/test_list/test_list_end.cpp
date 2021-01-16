////
//// Created by airat on 10.01.2021.
////
//
#include "test_list.hpp"

TEST(List_end, end_0_elements) {
    ft::list<int> l1(0);
    std::list<int> l2(0);

    ASSERT_EQ(*l1.end(), *l2.end());
}

TEST(List_end, end_1_element) {
    ft::list<int> l1(0);
    std::list<int> l2(0);

    l1.push_back(1);
    l2.push_back(1);
    ASSERT_EQ(*l1.end(), *l2.end());
}

TEST(List_end, more_elemets) {
    ft::list<int> l1(100);
    std::list<int> l2(100);

    ASSERT_EQ(*l1.end(), *l2.end());
}

TEST(List_end, const_end_0_element) {
    const ft::list<int> l1(0);
    const std::list<int> l2(0);
    ASSERT_EQ(*l1.end(), *l2.end());
}

TEST(List_end, const_end_1_element) {
    const ft::list<int> l1(1);
    std::list<int> l2(1);

    ASSERT_EQ(*l1.end(), *l2.end());
}

TEST(List_end, const_more_elemets) {
    const ft::list<int> l1(100);
    const std::list<int> l2(100);

    ASSERT_EQ(*l1.end(), *l2.end());
}