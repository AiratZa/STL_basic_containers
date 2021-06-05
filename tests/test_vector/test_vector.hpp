//
// Created by airat on 09.01.2021.
//

#ifndef FT_CONTAINERS_TEST_VECTOR_HPP
#define FT_CONTAINERS_TEST_VECTOR_HPP

#include <vector>
#include "../../source/vector.hpp"

#include <gtest/gtest.h>

template <typename T>
void ASSERT_VECTORS_EQ(const ft::vector<T>& v1, const std::vector<T>& v2) {
    typename ft::vector<T>::const_iterator it1 = v1.begin();
    typename std::vector<T>::const_iterator it2 = v2.begin();

    ASSERT_EQ(v1.size(), v2.size());
    while ( (it1 != v1.end()) || (it2 != v2.end()) ) {
        ASSERT_EQ(*it1, *it2);
        ++it1;
        ++it2;
    }
}
//
//template <typename T>
//void PRINT_LISTS_ELEMENTS_OPPOSITE(const ft::list<T>& l1, const std::list<T>& l2) {
//    typename ft::list<T>::const_iterator it1 = l1.begin();
//    typename std::list<T>::const_iterator it2 = l2.begin();
//
//    std::cout << "SIZE: " <<  l1.size() << "  |  " << l2.size() << std::endl << std::endl;
//
//    while ( (it1 != l1.end()) || (it2 != l2.end()) ) {
//        std::cout << *it1 << "  |  " << *it2 << std::endl;
//        ++it1;
//        ++it2;
//    }
//}


#endif //FT_CONTAINERS_TEST_VECTOR_HPP
