//
// Created by airat on 17.01.2021.
//

#include "test_stack.hpp"

TEST(Stack_constructor, stack) {
    ft::stack<int> s1;
    std::stack<int, std::list<int> > s2;

    ASSERT_STACKS_EQ(s1, s2);
}
