#include "test_list.hpp"

TEST(List_push_back, push_back_to_empty) {
    ft::list<int> l1(0);
    std::list<int> l2(0);

    ASSERT_EQ(l1.size(), l2.size());
    l1.push_back(1);
    l2.push_back(1);
    ASSERT_EQ(l1.size(), l2.size());
    ASSERT_EQ(*l1.begin(), *l2.begin());
    ASSERT_EQ(*l1.end(), *l2.end());
}

TEST(List_push_back, push_back_more_elements) {
    ft::list<int> l1(100, 32);
    std::list<int> l2(100, 32);

    ASSERT_EQ(l1.size(), l2.size());
    for (int i = 0; i < 3228; ++i) {
        l1.push_back(i);
        l2.push_back(i);
    }

    ASSERT_EQ(l1.size(),  l2.size());

    ft::list<int>::iterator it1 = l1.begin();
    std::list<int>::iterator it2 = l2.begin();

    for (int i = 0; i < 3228+100; ++i) {
        ASSERT_EQ(*it1,  *it2);
        ++it1;
        ++it2;
    }

}






