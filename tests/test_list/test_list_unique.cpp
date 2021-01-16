//
// Created by airat on 16.01.2021.
//

#include "test_list.hpp"
#include <math.h>

// just unique

TEST(List_unique, unique_0_elements) {
    ft::list<int> l1(0);
    std::list<int> l2(0);

    l1.unique();
    l2.unique();
    ASSERT_LISTS_EQ(l1, l2);
}


TEST(List_unique, unique_few_elements) {
    ft::list<int> l1(100, 256);
    std::list<int> l2(100, 256);

    l1.push_back(7);
    l2.push_back(7);
    ASSERT_LISTS_EQ(l1, l2);

    l1.unique();
    l2.unique();
    ASSERT_LISTS_EQ(l1, l2);

    l1.push_back(7);
    l2.push_back(7);
    ASSERT_LISTS_EQ(l1, l2);

    l1.unique();
    l2.unique();
    ASSERT_LISTS_EQ(l1, l2);
}

// with BinaryPredicate

// a binary predicate implemented as a function:
bool same_integral_part (double first, double second)
{ return ( int(first)==int(second) ); }

// a binary predicate implemented as a class:
struct is_near {
    bool operator() (double first, double second)
    { return (fabs(first-second)<5.0); }
};

TEST(List_unique, unique_binary_pred_0_elements) {

    ft::list<double> l1 (0);
    std::list<double> l2 (0);

    ASSERT_LISTS_EQ(l1, l2);

    l1.unique (same_integral_part);
    l2.unique (same_integral_part);
    ASSERT_LISTS_EQ(l1, l2);

    l1.unique (is_near());
    l2.unique (is_near());
    ASSERT_LISTS_EQ(l1, l2);

}

TEST(List_unique, unique_binary_pred_few_elements) {

    double mydoubles[]={ 12.15,  2.72, 73.0,  12.77,  3.14,
                         12.77, 73.35, 72.25, 15.3,  72.25 };

    ft::list<double> l1 (mydoubles,mydoubles+10);
    std::list<double> l2 (mydoubles,mydoubles+10);

    ASSERT_LISTS_EQ(l1, l2);

    l1.unique (same_integral_part);
    l2.unique (same_integral_part);
    ASSERT_LISTS_EQ(l1, l2);

    l1.unique (is_near());
    l2.unique (is_near());
    ASSERT_LISTS_EQ(l1, l2);

}
