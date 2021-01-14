////
//// Created by airat on 14.01.2021.
////
//
//#include "test_list.hpp"
//
//TEST(List_resize, resize_to_list_zero_size) {
//    ft::list<int> l1(0);
//    std::list<int> l2(0);
//
//    ft::list<int>::iterator it1;
//    std::list<int>::iterator it2;
//
//    ASSERT_EQ(l1.size(), l2.size());
//    l1.resize(100);
//    l2.resize(100);
//    ASSERT_EQ(l1.size(), l2.size());
//
//    it1 = l1.begin();
//    it2 = l2.begin();
//
//    while ((it1 != l1.end()) && (it1 != l1.end())) {
//        ASSERT_EQ(*it1, *it2);
//        ++it1;
//        ++it2;
//    }
//
//
//    l1.resize(65864);
//    l1.resize(65864);
//    ASSERT_EQ(l1.size(), l2.size());
//
//    it1 = l1.begin();
//    it2 = l2.begin();
//
//    while ((it1 != l1.end()) && (it1 != l1.end())) {
//        ASSERT_EQ(*it1, *it2);
//        ++it1;
//        ++it2;
//    }
//
//
//    l1.resize(0);
//    l1.resize(0);
//    ASSERT_EQ(l1.size(), l2.size());
//
//    it1 = l1.begin();
//    it2 = l2.begin();
//
//    while ((it1 != l1.end()) && (it1 != l1.end())) {
//        ASSERT_EQ(*it1, *it2);
//        ++it1;
//        ++it2;
//    }
//
//}
//
//TEST(List_resize, first_insert_to_few_elements) {
//    ft::list<int> l1(1);
//    std::list<int> l2(1);
//
//    ft::list<int>::iterator ite1 = l1.end();
//    std::list<int>::iterator ite2 = l2.end();
//
//    ft::list<int>::iterator check1 = l1.insert(ite1, 852);
//    std::list<int>::iterator check2 = l2.insert(ite2, 852);
//    ASSERT_EQ(*check1, *check2);
//
//    ASSERT_EQ(l1.size(), l2.size());
//
//    l2.push_back(654);
//    l2.push_back(654);
//
//    ft::list<int>::iterator it1 = l1.begin();
//    std::list<int>::iterator it2 = l2.begin();
//
//    ite1 = l1.end();
//    ite2 = l2.end();
//
//    while ((it1 != ite1) && (it2 != ite2)) {
//        ASSERT_EQ(*it1, *it2);
//        ++it1;
//        ++it2;
//    }
//}
//
//TEST(List_insert, first_insert_to_more_elements) {
//
//    ft::list<int> l1(9876, 1234);
//    std::list<int> l2(9876, 1234);
//
//    ft::list<int>::iterator it1;
//    std::list<int>::iterator it2;
//
//    ASSERT_EQ(l1.size(), l2.size());
//    l1.resize(62);
//    l2.resize(62);
//    ASSERT_EQ(l1.size(), l2.size());
//
//    it1 = l1.begin();
//    it2 = l2.begin();
//
//    while ((it1 != l1.end()) && (it1 != l1.end())) {
//        ASSERT_EQ(*it1, *it2);
//        ++it1;
//        ++it2;
//    }
//
//
//    l1.resize(6586);
//    l1.resize(6586);
//    ASSERT_EQ(l1.size(), l2.size());
//
//    it1 = l1.begin();
//    it2 = l2.begin();
//
//    while ((it1 != l1.end()) && (it1 != l1.end())) {
//        ASSERT_EQ(*it1, *it2);
//        ++it1;
//        ++it2;
//    }
//
//
//    l1.resize(0);
//    l1.resize(0);
//    ASSERT_EQ(l1.size(), l2.size());
//
//    it1 = l1.begin();
//    it2 = l2.begin();
//
//    while ((it1 != l1.end()) && (it1 != l1.end())) {
//        ASSERT_EQ(*it1, *it2);
//        ++it1;
//        ++it2;
//    }
//
//}