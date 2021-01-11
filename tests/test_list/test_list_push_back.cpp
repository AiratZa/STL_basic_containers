#include "test_list.hpp"

TEST(List_push_back, push_back) {
    ft::list<int> l1(1);
    std::list<int> l2(1);

    ASSERT_EQ(l1.size(), l2.size());
    l1.push_back(1);
    l2.push_back(1);
    ASSERT_EQ(l1.size(), l2.size());
}




