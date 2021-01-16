//
// Created by airat on 09.01.2021.
//

#ifndef FT_CONTAINERS_TEST_LIST_HPP
#define FT_CONTAINERS_TEST_LIST_HPP

#include <list>
#include "../../source/list.hpp"

#include <gtest/gtest.h>

template <typename T>
void ASSERT_LISTS_EQ(const ft::list<T>& l1, const std::list<T>& l2) {
    typename ft::list<T>::const_iterator it1 = l1.begin();
    typename std::list<T>::const_iterator it2 = l2.begin();

    ASSERT_EQ(l1.size(), l2.size());
    while ( (it1 != l1.end()) || (it2 != l2.end()) ) {
        ASSERT_EQ(*it1, *it2);
        ++it1;
        ++it2;
    }
}

#endif //FT_CONTAINERS_TEST_LIST_HPP
