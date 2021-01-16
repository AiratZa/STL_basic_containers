//
// Created by airat on 16.01.2021.
//

#include "test_list.hpp"

// ==
TEST(List_relational_operators, equal_few_elements) {
    ft::list<std::string> l1(0);
    ft::list<std::string> l1_2(0);

    std::list<std::string> l2(0);
    std::list<std::string> l2_2(0);

    ASSERT_EQ((l1 == l1_2), (l2 == l2_2));

    l1.push_back("1");
    l2.push_back("1");
    ASSERT_EQ((l1 == l1_2), (l2 == l2_2));

}

TEST(List_relational_operators, equal_more_elements) {
    ft::list<int> l1(100, 10);
    ft::list<int> l1_2(50, 987);

    std::list<int> l2(100, 10);
    std::list<int> l2_2(50, 987);

    ASSERT_EQ((l1 == l1_2), (l2 == l2_2));

    l1.push_back(-789);
    l2.push_back(-789);
    ASSERT_EQ((l1 == l1_2), (l2 == l2_2));

}


// !=
TEST(List_relational_operators, not_equal_few_elements) {
    ft::list<std::string> l1(0);
    ft::list<std::string> l1_2(0);

    std::list<std::string> l2(0);
    std::list<std::string> l2_2(0);

    ASSERT_EQ((l1 != l1_2), (l2 != l2_2));

    l1.push_back("1");
    l2.push_back("1");
    ASSERT_EQ((l1 != l1_2), (l2 != l2_2));

}

TEST(List_relational_operators, not_equal_more_elements) {
    ft::list<int> l1(100, 10);
    ft::list<int> l1_2(50, 987);

    std::list<int> l2(100, 10);
    std::list<int> l2_2(50, 987);

    ASSERT_EQ((l1 != l1_2), (l2 != l2_2));

    l1.push_back(-789);
    l2.push_back(-789);
    ASSERT_EQ((l1 != l1_2), (l2 != l2_2));
}

// <
TEST(List_relational_operators, less_few_elements) {
    ft::list<std::string> l1(0);
    ft::list<std::string> l1_2(0);

    std::list<std::string> l2(0);
    std::list<std::string> l2_2(0);

    ASSERT_EQ((l1 < l1_2), (l2 < l2_2));

    l1.push_back("1");
    l2.push_back("1");
    ASSERT_EQ((l1 < l1_2), (l2 < l2_2));

}

TEST(List_relational_operators, less_more_elements) {
    ft::list<int> l1(100, 10);
    ft::list<int> l1_2(50, 987);

    std::list<int> l2(100, 10);
    std::list<int> l2_2(50, 987);

    ASSERT_EQ((l1 < l1_2), (l2 < l2_2));

    l1.push_back(-789);
    l2.push_back(-789);
    ASSERT_EQ((l1 < l1_2), (l2 < l2_2));
}


// <=
TEST(List_relational_operators, less_equal_few_elements) {
    ft::list<std::string> l1(0);
    ft::list<std::string> l1_2(0);

    std::list<std::string> l2(0);
    std::list<std::string> l2_2(0);

    ASSERT_EQ((l1 <= l1_2), (l2 <= l2_2));

    l1.push_back("1");
    l2.push_back("1");
    ASSERT_EQ((l1 <= l1_2), (l2 <= l2_2));

}

TEST(List_relational_operators, less_equal_more_elements) {
    ft::list<int> l1(100, 10);
    ft::list<int> l1_2(50, 987);

    std::list<int> l2(100, 10);
    std::list<int> l2_2(50, 987);

    ASSERT_EQ((l1 <= l1_2), (l2 <= l2_2));

    l1.push_back(-789);
    l2.push_back(-789);
    ASSERT_EQ((l1 <= l1_2), (l2 <= l2_2));
}

// >
TEST(List_relational_operators, more_few_elements) {
    ft::list<std::string> l1(0);
    ft::list<std::string> l1_2(0);

    std::list<std::string> l2(0);
    std::list<std::string> l2_2(0);

    ASSERT_EQ((l1 > l1_2), (l2 > l2_2));

    l1.push_back("1");
    l2.push_back("1");
    ASSERT_EQ((l1 > l1_2), (l2 > l2_2));

}

TEST(List_relational_operators, more_more_elements) {
    ft::list<int> l1(100, 10);
    ft::list<int> l1_2(50, 987);

    std::list<int> l2(100, 10);
    std::list<int> l2_2(50, 987);

    ASSERT_EQ((l1 > l1_2), (l2 > l2_2));

    l1.push_back(-789);
    l2.push_back(-789);
    ASSERT_EQ((l1 > l1_2), (l2 > l2_2));
}


// >=
TEST(List_relational_operators, more_equal_few_elements) {
    ft::list<std::string> l1(0);
    ft::list<std::string> l1_2(0);

    std::list<std::string> l2(0);
    std::list<std::string> l2_2(0);

    ASSERT_EQ((l1 >= l1_2), (l2 >= l2_2));

    l1.push_back("1");
    l2.push_back("1");
    ASSERT_EQ((l1 >= l1_2), (l2 >= l2_2));

}

TEST(List_relational_operators, more_equal_more_elements) {
    ft::list<int> l1(100, 10);
    ft::list<int> l1_2(50, 987);

    std::list<int> l2(100, 10);
    std::list<int> l2_2(50, 987);

    ASSERT_EQ((l1 >= l1_2), (l2 >= l2_2));

    l1.push_back(-789);
    l2.push_back(-789);
    ASSERT_EQ((l1 >= l1_2), (l2 >= l2_2));
}

