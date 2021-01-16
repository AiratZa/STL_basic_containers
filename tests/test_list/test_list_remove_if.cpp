//
// Created by airat on 16.01.2021.
//

#include "test_list.hpp"

// a predicate implemented as a function:
bool single_digit (const int& value) { return (value<10); }

// a predicate implemented as a class:
struct is_odd {
    bool operator() (const int& value) { return (value%2)==1; }
};

TEST(List_remove_if, remove_if_0_elements) {
    ft::list<int> l1(0);
    std::list<int> l2(0);

    l1.remove_if(single_digit);
    l2.remove_if(single_digit);
    ASSERT_LISTS_EQ(l1, l2);
}


TEST(List_remove_if, remove_if_few_elements) {
    ft::list<int> l1(100, 256);
    std::list<int> l2(100, 256);

    l1.push_back(7);
    l2.push_back(7);

    ASSERT_LISTS_EQ(l1, l2);

    l1.remove_if(is_odd());
    l2.remove_if(is_odd());
    ASSERT_LISTS_EQ(l1, l2);

    l1.remove_if(single_digit);
    l2.remove_if(single_digit);
    ASSERT_LISTS_EQ(l1, l2);

}


