//
// Created by airat on 15.01.2021.
//

#include "test_list.hpp"


TEST(List_erase, erase_to_one_element) {
    ft::list<int> l1(1);
    std::list<int> l2(1);
    ft::list<int>::iterator tmp1;
    std::list<int>::iterator tmp2;

    ASSERT_EQ(l1.size(), l2.size());

    ft::list<int>::iterator ite1 = l1.begin();
    std::list<int>::iterator ite2 = l2.begin();

    ASSERT_EQ(l1.size(), l2.size());

    tmp1 = l1.erase(ite1);
    tmp2 = l2.erase(ite2);
    ASSERT_EQ(l1.size(), l2.size());
    ASSERT_EQ(*tmp1, *tmp2);
}

TEST(List_erase, erase_to_more_elements) {
    ft::list<int> l1(100, 32);
    std::list<int> l2(100, 32);

    ft::list<int>::iterator tmp1;
    std::list<int>::iterator tmp2;

    ASSERT_EQ(l1.size(), l2.size());

    for (int i = 0; i < 3228; ++i) {
        l1.push_back(i);
        l2.push_back(i);
        ASSERT_EQ(l1.size(), l2.size());
    }

    ASSERT_EQ(l1.size(), l2.size());

    tmp1 = l1.begin();
    tmp2 = l2.begin();

    while ( (tmp1 != l1.end()) && (tmp2 != l2.end()) ) {
        tmp1 = l1.erase(tmp1);
        tmp2 = l2.erase(tmp2);
        ASSERT_EQ(l1.size(), l2.size());
        ASSERT_EQ(*tmp1, *tmp2);
    }

}

//with range of iterators

TEST(List_erase, erase_to_one_element_iterators_range) {
    ft::list<int> l1(1);
    std::list<int> l2(1);
    ft::list<int>::iterator tmp1;
    std::list<int>::iterator tmp2;

    ASSERT_EQ(l1.size(), l2.size());


    ASSERT_EQ(l1.size(), l2.size());

    tmp1 = l1.erase(l1.begin(), l1.end());
    tmp2 = l2.erase(l2.begin(), l2.end());
    ASSERT_EQ(l1.size(), l2.size());
    ASSERT_EQ(*tmp1, *tmp2);
}

TEST(List_erase, erase_to_more_elements_iterators_range) {
    ft::list<int> l1(100, 32);
    std::list<int> l2(100, 32);

    ft::list<int>::iterator tmp1;
    std::list<int>::iterator tmp2;

    ASSERT_EQ(l1.size(), l2.size());

    for (int i = 0; i < 3228; ++i) {
        l1.push_back(i);
        l2.push_back(i);
        ASSERT_EQ(l1.size(), l2.size());
    }

    ASSERT_EQ(l1.size(), l2.size());

    tmp1 = l1.erase(l1.begin(), l1.end());
    tmp2 = l2.erase(l2.begin(), l2.end());

    ASSERT_EQ(l1.size(), l2.size());
    ASSERT_EQ(*tmp1, *tmp2);

}

