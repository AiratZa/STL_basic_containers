//
// Created by airat on 14.01.2021.
//

#include "test_list.hpp"

TEST(List_empty_clear_maxSize, zero_init_elements) {
    ft::list<int> l1(0);
    std::list<int> l2(0);

    ASSERT_EQ(l1.empty(), l2.empty());

    ASSERT_EQ(l1.size(), l2.size());
    l1.clear();
    l2.clear();
    ASSERT_EQ(l1.empty(), l2.empty());
    ASSERT_EQ(l1.size(), l2.size());
    l1.push_back(1);
    l2.push_back(1);
    l1.push_back(2);
    l2.push_back(2);
    ASSERT_EQ(l1.empty(), l2.empty());
    ASSERT_EQ(l1.size(), l2.size());
    l1.clear();
    l2.clear();
    ASSERT_EQ(l1.empty(), l2.empty());
    ASSERT_EQ(l1.size(), l2.size());
}

TEST(List_empty_clear_maxSize, one_init_elements) {
    ft::list<int> l1(1, 5);
    std::list<int> l2(1, 5);

    ASSERT_EQ(l1.empty(), l2.empty());
    ASSERT_EQ(l1.size(), l2.size());
    ASSERT_EQ(l1.max_size(), l2.max_size());
    l1.clear();
    l2.clear();
    ASSERT_EQ(l1.empty(), l2.empty());
    ASSERT_EQ(l1.size(), l2.size());
    ASSERT_EQ(l1.max_size(), l2.max_size());
    l1.push_back(1);
    l2.push_back(1);
    l1.push_back(2);
    l2.push_back(2);
    ASSERT_EQ(l1.empty(), l2.empty());
    ASSERT_EQ(l1.size(), l2.size());
    ASSERT_EQ(l1.max_size(), l2.max_size());
    l1.clear();
    l2.clear();
    ASSERT_EQ(l1.empty(), l2.empty());
    ASSERT_EQ(l1.size(), l2.size());
    ASSERT_EQ(l1.max_size(), l2.max_size());
}

TEST(List_empty_clear_maxSize, thousand_init_elements) {
    ft::list<int> l1(1000, 100500);
    std::list<int> l2(1000, 100500);

    ASSERT_EQ(l1.empty(), l2.empty());
    ASSERT_EQ(l1.size(), l2.size());
    l1.clear();
    l2.clear();
    ASSERT_EQ(l1.size(), l2.size());
    ASSERT_EQ(l1.empty(), l2.empty());
    l1.push_back(1);
    l2.push_back(1);
    l1.push_back(2);
    l2.push_back(2);
    ASSERT_EQ(l1.size(), l2.size());
    ASSERT_EQ(l1.empty(), l2.empty());
    l1.clear();
    l2.clear();
    ASSERT_EQ(l1.size(), l2.size());
    ASSERT_EQ(l1.empty(), l2.empty());
}




