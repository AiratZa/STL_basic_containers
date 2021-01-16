//
// Created by airat on 16.01.2021.
//
#include "test_list.hpp"

//entire list (1)

TEST(List_splice, splice_entire_list ) {
    ft::list<int> l1_1(3, 22);
    ft::list<int> l1_2(0);

    std::list<int> l2_1(3, 22);
    std::list<int> l2_2(0);

    ft::list<int>::iterator it1;
    std::list<int>::iterator it2;

    for (int i=1; i<=4; ++i)
        l1_1.push_back(i);      // l1_1: 1 2 3 4

    for (int i=1; i<=3; ++i)
        l1_2.push_back(i*10);   // l1_2: 10 20 30


    for (int i=1; i<=4; ++i)
        l2_1.push_back(i);      // l2_1: 1 2 3 4

    for (int i=1; i<=3; ++i)
        l2_2.push_back(i*10);   // l2_2: 10 20 30

    it1 = l1_1.begin();
    it2 = l2_1.begin();

    ++it1;
    ++it2;

    l1_1.splice (it1, l1_1);
    l2_1.splice (it2, l2_1);

    ASSERT_EQ(l1_1.size(), l2_1.size());
    ASSERT_EQ(l1_2.size(), l2_2.size());


    ft::list<int>::iterator itb1 = l1_1.begin();
    std::list<int>::iterator itb2 = l2_1.begin();

    while ( (itb1 != l1_1.end()) || (itb2 != l2_1.end()) ) {
        ASSERT_EQ(*itb1, *itb2);
        ++itb1;
        ++itb2;
    }

}

//single element (2) bag
TEST(List_splice, splice_single_element_bag) {
    ft::list<int> l1_1(0);
    ft::list<int> l1_2(0);

    std::list<int> l2_1(0);
    std::list<int> l2_2(0);

    ft::list<int>::iterator it1;
    std::list<int>::iterator it2;

    for (int i=1; i<=4; ++i)
        l1_1.push_back(i);      // l1_1: 1 2 3 4

    for (int i=1; i<=3; ++i)
        l1_2.push_back(i*10);   // l1_2: 10 20 30


    for (int i=1; i<=4; ++i)
        l2_1.push_back(i);      // l2_1: 1 2 3 4

    for (int i=1; i<=3; ++i)
        l2_2.push_back(i*10);   // l2_2: 10 20 30

    it1 = l1_1.begin();
    it2 = l2_1.begin();

    ++it1;
    ++it2;

    ft::list<int>::iterator itb_1_2 = l1_2.begin();
    std::list<int>::iterator itb_2_2 = l2_2.begin();

    l1_1.splice (it1, l1_1, itb_1_2); // 1 10 2 3 4
    l2_1.splice (it2, l2_1, itb_2_2); // 1 10 2 3 4
    // size bag, reimplemented in C++11

    ASSERT_EQ(l1_1.size(), l2_1.size());
    ASSERT_EQ(l1_2.size(), l2_2.size());


    ft::list<int>::iterator itb1 = l1_1.begin();
    std::list<int>::iterator itb2 = l2_1.begin();

    while ( (itb1 != l1_1.end()) || (itb2 != l2_1.end()) ) {
        ASSERT_EQ(*itb1, *itb2);
        ++itb1;
        ++itb2;
    }

}

//single element (2)
TEST(List_splice, splice_single_element) {
    ft::list<int> l1_1(0);
    ft::list<int> l1_2(0);

    std::list<int> l2_1(0);
    std::list<int> l2_2(0);

    ft::list<int>::iterator it1;
    std::list<int>::iterator it2;

    for (int i=1; i<=4; ++i)
        l1_1.push_back(i);      // l1_1: 1 2 3 4

    for (int i=1; i<=3; ++i)
        l1_2.push_back(i*10);   // l1_2: 10 20 30


    for (int i=1; i<=4; ++i)
        l2_1.push_back(i);      // l2_1: 1 2 3 4

    for (int i=1; i<=3; ++i)
        l2_2.push_back(i*10);   // l2_2: 10 20 30

    it1 = l1_1.begin();
    it2 = l2_1.begin();

    ++it1;
    ++it2;

    ft::list<int>::iterator itb_1_2 = l1_2.begin();
    std::list<int>::iterator itb_2_2 = l2_2.begin();

    l1_1.splice (it1, l1_2, itb_1_2); // 1 10 2 3 4
    l2_1.splice (it2, l2_2, itb_2_2); // 1 10 2 3 4

    ASSERT_EQ(l1_1.size(), l2_1.size());
    ASSERT_EQ(l1_2.size(), l2_2.size());


    ft::list<int>::iterator itb1 = l1_1.begin();
    std::list<int>::iterator itb2 = l2_1.begin();

    while ( (itb1 != l1_1.end()) || (itb2 != l2_1.end()) ) {
        ASSERT_EQ(*itb1, *itb2);
        ++itb1;
        ++itb2;
    }

}


//element range (3)
TEST(List_splice, splice_element_range) {
    ft::list<int> l1_1(0);
    std::list<int> l2_1(0);

    l1_1.push_back(1);
    l1_1.push_back(10);
    l1_1.push_back(20);
    l1_1.push_back(30);
    l1_1.push_back(3);
    l1_1.push_back(4);

    l2_1.push_back(1);
    l2_1.push_back(10);
    l2_1.push_back(20);
    l2_1.push_back(30);
    l2_1.push_back(3);
    l2_1.push_back(4);


    ASSERT_EQ(l1_1.size(), l2_1.size());


    ft::list<int>::iterator itb1 = l1_1.begin();
    std::list<int>::iterator itb2 = l2_1.begin();

    ++itb1;
    ++itb1;
    ++itb1;

    ++itb2;
    ++itb2;
    ++itb2;

    l1_1.splice ( l1_1.begin(), l1_1, itb1, l1_1.end());
    l2_1.splice ( l2_1.begin(), l2_1, itb2, l2_1.end());

    ASSERT_EQ(l1_1.size(), l2_1.size());


    itb1 = l1_1.begin();
    itb2 = l2_1.begin();

    while ( (itb1 != l1_1.end()) || (itb2 != l2_1.end()) ) {
        ASSERT_EQ(*itb1, *itb2);
        ++itb1;
        ++itb2;
    }

}


