//
// Created by airat on 17.01.2021.
//

#include "test_stack.hpp"

TEST(Stack, all)
{
// CTOR
    ft::stack<int> q1;
    std::stack<int, std::list<int> > q2;

    ASSERT_STACKS_EQ(q1, q2);
// EMPTY SIZE 1
    ASSERT_EQ(q1.empty(), q2.empty());
    ASSERT_EQ(q1.size(), q2.size());

// PUSH TOP
    for (int i = 0; i < 3; ++i) {
        q1.push(i);
        q2.push(i);
        ASSERT_EQ(q1.top(), q2.top());
    }
    ASSERT_STACKS_EQ(q1, q2);

// EMPTY SIZE 2
    ASSERT_EQ(q1.empty(), q2.empty());
    ASSERT_EQ(q1.size(), q2.size());

// POP
    for (int i = 0; i < 3; ++i) {
        ASSERT_EQ(q1.top(), q2.top());
        q1.pop();
        q2.pop();
    }
    ASSERT_STACKS_EQ(q1, q2);
}


TEST(Stack, relational_operators)
{
    ft::stack<int> q1;
    ft::stack<int> q2;

    {
        ASSERT_TRUE(q1 == q2);
        ASSERT_EQ(q1.size(), q2.size());

        for (int i = 0; i < 3; ++i) {
            q1.push(i);
            q2.push(i);
            ASSERT_EQ(q1.top(), q2.top());
        }

        ASSERT_TRUE(q1 == q2);
        ASSERT_EQ(q1.size(), q2.size());
    }

    {
        // 1
        q2.push(100500);

        ASSERT_TRUE(q1 < q2);
        ASSERT_TRUE(q1 <= q2);

        ASSERT_TRUE(q1 != q2);

        ASSERT_TRUE(q2 > q1);
        ASSERT_TRUE(q2 >= q1);

        // 2
        q1.push(0);

        ASSERT_TRUE(q1 < q2);
        ASSERT_TRUE(q1 <= q2);

        ASSERT_TRUE(q1 != q2);

        ASSERT_TRUE(q2 > q1);
        ASSERT_TRUE(q2 >= q1);
    }
}