//
// Created by airat on 14.01.2021.
//

#include "test_list.hpp"

TEST(List_front_back, front_back_to_few_elements) {
    ft::list<int> l1(1);
    std::list<int> l2(1);

    ASSERT_EQ(l1.front(), l2.front());
    ASSERT_EQ(l1.back(), l2.back());
    l1.push_back(951);
    l2.push_back(951);
    ASSERT_EQ(l1.front(), l2.front());
    ASSERT_EQ(l1.back(), l2.back());
    l1.push_front(753);
    l2.push_front(753);
    ASSERT_EQ(l1.front(), l2.front());
    ASSERT_EQ(l1.back(), l2.back());
}

TEST(List_front_back, front_back_to_more_elements) {
    ft::list<int> l1(100, 32);
    std::list<int> l2(100, 32);

    ASSERT_EQ(l1.front(), l2.front());
    ASSERT_EQ(l1.back(), l2.back());
    for (int i = 0; i < 3228; ++i) {
        l1.push_back(i);
        l2.push_back(i);
    }

    for (int i = 4000; i > 3228; --i) {
        l1.push_front(i);
        l2.push_front(i);
    }
    ASSERT_EQ(l1.front(), l2.front());
    ASSERT_EQ(l1.back(), l2.back());

}






