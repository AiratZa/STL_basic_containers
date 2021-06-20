//
// Created by airat on 14.06.2021.
//

#ifndef FT_CONTAINERS_TEST_MAP_HPP
#define FT_CONTAINERS_TEST_MAP_HPP

#include "../../source/map.hpp"
#include <gtest/gtest.h>
#include <map>
#include <string>

template <class S, class T>
void ASSERT_MAPS_EQ(const ft::map<S, T>& v1, const std::map<S, T>& v2) {
    typename ft::map<S, T>::const_iterator it1 = v1.begin();
    typename std::map<S, T>::const_iterator it2 = v2.begin();

    ASSERT_EQ(v1.size(), v2.size());
    while ( (it1 != v1.end()) || (it2 != v2.end()) ) {
        ASSERT_EQ(*it1, *it2);
        ++it1;
        ++it2;
    }
}


#endif //FT_CONTAINERS_TEST_MAP_HPP
