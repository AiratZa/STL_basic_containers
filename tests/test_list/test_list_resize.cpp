////
//// Created by airat on 14.01.2021.
////

#include "test_list.hpp"

TEST(List_resize, resize_to_list_zero_size) {
    ft::list<int> l1(0);
    std::list<int> l2(0);

    ft::list<int>::iterator it1;
    std::list<int>::iterator it2;

    ASSERT_EQ(l1.size(), l2.size());
    l1.resize(100);
    l2.resize(100);
    ASSERT_EQ(l1.size(), l2.size());

    it1 = l1.begin();
    it2 = l2.begin();

    while ((it1 != l1.end()) || (it1 != l1.end())) {
        ASSERT_EQ(*it1, *it2);
        ++it1;
        ++it2;
    }


    l1.resize(65864);
    l2.resize(65864);
    ASSERT_EQ(l1.size(), l2.size());

    it1 = l1.begin();
    it2 = l2.begin();

    while ((it1 != l1.end()) || (it1 != l1.end())) {
        ASSERT_EQ(*it1, *it2);
        ++it1;
        ++it2;
    }


    l1.resize(0);
    l2.resize(0);
    ASSERT_EQ(l1.size(), l2.size());

    it1 = l1.begin();
    it2 = l2.begin();

    while ((it1 != l1.end()) || (it1 != l1.end())) {
        ASSERT_EQ(*it1, *it2);
        ++it1;
        ++it2;
    }

}

TEST(List_resize, resize_to_list_non_zero_size) {
    ft::list<int> l1(100, 54321);
    std::list<int> l2(100, 54321);

    ft::list<int>::iterator it1;
    std::list<int>::iterator it2;

    ASSERT_EQ(l1.size(), l2.size());
    l1.resize(100);
    l2.resize(100);
    ASSERT_EQ(l1.size(), l2.size());

    it1 = l1.begin();
    it2 = l2.begin();

    while ((it1 != l1.end()) || (it1 != l1.end())) {
        ASSERT_EQ(*it1, *it2);
        ++it1;
        ++it2;
    }


    l1.resize(65864);
    l2.resize(65864);
    ASSERT_EQ(l1.size(), l2.size());

    it1 = l1.begin();
    it2 = l2.begin();

    while ((it1 != l1.end()) || (it1 != l1.end())) {
        ASSERT_EQ(*it1, *it2);
        ++it1;
        ++it2;
    }


    l1.resize(0);
    l2.resize(0);
    ASSERT_EQ(l1.size(), l2.size());

    it1 = l1.begin();
    it2 = l2.begin();

    while ((it1 != l1.end()) || (it1 != l1.end())) {
        ASSERT_EQ(*it1, *it2);
        ++it1;
        ++it2;
    }

}

