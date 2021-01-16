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

    while ( (itb1 != l1_1.end()) && (itb2 != l2_1.end()) ) {
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

//    ft::list<int>::iterator itb_1_2 = l1_2.begin();
    std::list<int>::iterator itb_2_2 = l2_2.begin();


        if (__cplusplus == 201703L) std::cout << "C++17\n";
        else if (__cplusplus == 201402L) std::cout << "C++14\n";
        else if (__cplusplus == 201103L) std::cout << "C++11\n";
        else if (__cplusplus == 199711L) std::cout << "C++98\n";
        else std::cout << "pre-standard C++\n";

//    l1_1.splice (it1, l1_1, itb_1_2); // 1 10 2 3 4
    l2_1.splice (it2, l2_1, itb_2_2); // 1 10 2 3 4


//    ft::list<int>::iterator itb1 = l1_1.begin();
    std::list<int>::iterator itb2 = l2_1.begin();

    while ( (itb2 != l2_1.end()) ) {
//        ASSERT_EQ(*itb1, *itb2);
        std::cout << *itb2 << std::endl;
        ++itb2;
//        ++itb2;
    }

    std::cout << l2_1.size() << " " << l2_2.size() << std::endl;


//    ASSERT_EQ(l1_1.size(), l2_1.size());
//    ASSERT_EQ(l1_2.size(), l2_2.size());
//
//
//    ft::list<int>::iterator itb1 = l1_1.begin();
//    std::list<int>::iterator itb2 = l2_1.begin();
//
//    while ( (itb1 != l1_1.end()) && (itb2 != l2_1.end()) ) {
////        ASSERT_EQ(*itb1, *itb2);
//        std::cout << *itb2 << std::endl;
//        ++itb1;
//        ++itb2;
//    }

}

