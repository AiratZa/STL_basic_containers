//
// Created by airat on 14.01.2021.
//

#include "test_list.hpp"

//single element (1)

TEST(List_insert, first_insert_to_few_elements) {
    ft::list<int> l1(1);
    std::list<int> l2(1);

    ft::list<int>::iterator ite1 = l1.end();
    std::list<int>::iterator ite2 = l2.end();

    ft::list<int>::iterator check1 = l1.insert(ite1, 852);
    std::list<int>::iterator check2 = l2.insert(ite2, 852);
    ASSERT_EQ(*check1, *check2);

    ASSERT_EQ(l1.size(), l2.size());

    l1.push_back(654);
    l2.push_back(654);

    ft::list<int>::iterator it1 = l1.begin();
    std::list<int>::iterator it2 = l2.begin();

    ite1 = l1.end();
    ite2 = l2.end();

    while ((it1 != ite1) || (it2 != ite2)) {
        ASSERT_EQ(*it1, *it2);
        ++it1;
        ++it2;
    }
}

TEST(List_insert, first_insert_to_more_elements) {
    ft::list<int> l1(100, 32);
    std::list<int> l2(100, 32);

    ft::list<int>::iterator ite1;
    std::list<int>::iterator ite2;

    ft::list<int>::iterator check1;
    std::list<int>::iterator check2;

    ASSERT_EQ(l1.size(), l2.size());

    for (int i = 0; i < 3228; ++i) {
        ite1 = l1.end();
        ite2 = l2.end();

        check1 = l1.insert(ite1, i);
        check2 = l2.insert(ite2, i);

        ASSERT_EQ(*check1, *check2);
        ASSERT_EQ(l1.size(), l2.size());
    }

    ASSERT_EQ(l1.size(), l2.size());

    l1.push_back(654);
    l2.push_back(654);

    ASSERT_EQ(l1.size(), l2.size());

    ft::list<int>::iterator it1 = l1.begin();
    std::list<int>::iterator it2 = l2.begin();

    ite1 = l1.end();
    ite2 = l2.end();

    while ((it1 != ite1) || (it2 != ite2)) {
        ASSERT_EQ(*it1, *it2);
        ++it1;
        ++it2;
    }

}





//fill (2)

TEST(List_insert, second_insert_to_few_elements) {
    ft::list<int> l1(1);
    std::list<int> l2(1);

    ft::list<int>::iterator ite1 = l1.end();
    std::list<int>::iterator ite2 = l2.end();

    l1.insert(ite1, 852, 657);
    l2.insert(ite2, 852, 657);

    ASSERT_EQ(l1.size(), l2.size());

    l1.push_back(778855);
    l2.push_back(778855);

    ft::list<int>::iterator it1 = l1.begin();
    std::list<int>::iterator it2 = l2.begin();

    ite1 = l1.end();
    ite2 = l2.end();

    while ((it1 != ite1) || (it2 != ite2)) {
        ASSERT_EQ(*it1, *it2);
        ++it1;
        ++it2;
    }
}

TEST(List_insert, second_insert_to_more_elements) {
    ft::list<int> l1(100, 32);
    std::list<int> l2(100, 32);

    ft::list<int>::iterator ite1;
    std::list<int>::iterator ite2;

    ASSERT_EQ(l1.size(), l2.size());

    for (int i = 0; i < 322; ++i) {
        ite1 = l1.end();
        ite2 = l2.end();

        l1.insert(ite1, i, i);
        l2.insert(ite2, i, i);

        ASSERT_EQ(l1.size(), l2.size());
    }

    ASSERT_EQ(l1.size(), l2.size());

    l1.push_back(654);
    l2.push_back(654);

    ASSERT_EQ(l1.size(), l2.size());

    ft::list<int>::iterator it1 = l1.begin();
    std::list<int>::iterator it2 = l2.begin();

    ite1 = l1.end();
    ite2 = l2.end();

    while ((it1 != ite1) || (it2 != ite2)) {
        ASSERT_EQ(*it1, *it2);
        ++it1;
        ++it2;
    }

}




