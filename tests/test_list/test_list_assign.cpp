//
// Created by airat on 16.01.2021.
//

#include "test_list.hpp"

// range (1)

TEST(List_assign, assign_range_to_empty_list ) {
    ft::list<int> l1_1(0);
    ft::list<int> l1_2(0);

    std::list<int> l2_1(0);
    std::list<int> l2_2(0);

    ft::list<int>::iterator it1;
    std::list<int>::iterator it2;



    for (int i=1; i<=3; ++i) {
        l1_2.push_back(i * 10);   // l1_2: 10 20 30
        l2_2.push_back(i * 10);   // l2_2: 10 20 30
    }

    for (int i=1; i<=3; ++i)

    it1 = l1_2.begin();
    it2 = l2_2.begin();

    ++it1;
    ++it2;

    ASSERT_EQ(l1_1.size(), l2_1.size());
    ASSERT_EQ(l1_2.size(), l2_2.size());

    l1_1.assign(it1, l1_2.end());
    l2_1.assign(it2, l2_2.end());

    ASSERT_EQ(l1_1.size(), l2_1.size());
    ASSERT_EQ(l1_2.size(), l2_2.size());

    it1 = l1_1.begin();
    it2 = l2_1.begin();

    while ( (it1 != l1_1.end()) || (it2 != l2_1.end()) ) {
        ASSERT_EQ(*it1, *it2);
        ++it1;
        ++it2;
    }

    it1 = l1_2.begin();
    it2 = l2_2.begin();

    while ( (it1 != l1_2.end()) || (it2 != l2_2.end()) ) {
        ASSERT_EQ(*it1, *it2);
        ++it1;
        ++it2;
    }

}

TEST(List_assign, assign_range_to_non_empty_list ) {
    ft::list<int> l1_1(100, 654);
    ft::list<int> l1_2(0);

    std::list<int> l2_1(100, 654);
    std::list<int> l2_2(0);

    ft::list<int>::iterator it1;
    std::list<int>::iterator it2;



    for (int i=1; i<=3; ++i) {
        l1_2.push_back(i * 10);   // l1_2: 10 20 30
        l2_2.push_back(i * 10);   // l2_2: 10 20 30
    }

    it1 = l1_2.begin();
    it2 = l2_2.begin();

    ++it1;
    ++it2;

    ASSERT_EQ(l1_1.size(), l2_1.size());
    ASSERT_EQ(l1_2.size(), l2_2.size());

    l1_1.assign(it1, l1_2.end());
    l2_1.assign(it2, l2_2.end());

    ASSERT_EQ(l1_1.size(), l2_1.size());
    ASSERT_EQ(l1_2.size(), l2_2.size());

    it1 = l1_1.begin();
    it2 = l2_1.begin();

    while ( (it1 != l1_1.end()) || (it2 != l2_1.end()) ) {
        ASSERT_EQ(*it1, *it2);
        ++it1;
        ++it2;
    }

    it1 = l1_2.begin();
    it2 = l2_2.begin();

    while ( (it1 != l1_2.end()) || (it2 != l2_2.end()) ) {
        ASSERT_EQ(*it1, *it2);
        ++it1;
        ++it2;
    }

}


// fill (2)

TEST(List_assign, assign_fill_to_empty_list ) {
    ft::list<int> l1_1(0);
    std::list<int> l2_1(0);

    ft::list<int>::iterator it1;
    std::list<int>::iterator it2;

    for (int i=1; i<=3; ++i) {
        l1_1.push_back(i * 10);   // l1_1: 10 20 30
        l2_1.push_back(i * 10);   // l2_1: 10 20 30
    }

    ASSERT_EQ(l1_1.size(), l2_1.size());

    l1_1.assign(100, 500);
    l2_1.assign(100, 500);

    ASSERT_EQ(l1_1.size(), l2_1.size());

    it1 = l1_1.begin();
    it2 = l2_1.begin();

    while ( (it1 != l1_1.end()) || (it2 != l2_1.end()) ) {
        ASSERT_EQ(*it1, *it2);
        ++it1;
        ++it2;
    }

}



TEST(List_assign, assign_fill_to_non_empty_list ) {
    ft::list<int> l1_1(100, 654);
    std::list<int> l2_1(100, 654);

    ft::list<int>::iterator it1;
    std::list<int>::iterator it2;


    ASSERT_EQ(l1_1.size(), l2_1.size());

    l1_1.assign(500, 100);
    l2_1.assign(500, 100);

    ASSERT_EQ(l1_1.size(), l2_1.size());

    it1 = l1_1.begin();
    it2 = l2_1.begin();

    while ( (it1 != l1_1.end()) || (it2 != l2_1.end()) ) {
        ASSERT_EQ(*it1, *it2);
        ++it1;
        ++it2;
    }

}

