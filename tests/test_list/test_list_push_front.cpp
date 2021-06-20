//
// Created by airat on 09.01.2021.
//

#include "test_list.hpp"

#include "test_list.hpp"

TEST(List_push_back, push_front_more_elements) {
    ft::list<int> l1(128, 32);
    std::list<int> l2(128, 32);

    ASSERT_EQ(l1.size(), l2.size());
    for (int i = 0; i < 6416; ++i) {
        l1.push_front(i);
        l2.push_front(i);
    }

    ASSERT_EQ(l1.size(),  l2.size());

    ft::list<int>::iterator it1 = l1.begin();
    std::list<int>::iterator it2 = l2.begin();

    for (int i = 0; i < 6416+128; ++i) {
        ASSERT_EQ(*it1,  *it2);
        ++it1;
        ++it2;
    }

}






