//
// Created by airat on 17.01.2021.
//

#include "test_queue.hpp"

TEST(Queue, all)
{
// CTOR
    ft::queue<int> q1;
    std::queue<int, std::list<int> > q2;

    ASSERT_QUEUES_EQ(q1, q2);
// EMPTY SIZE 1
    ASSERT_EQ(q1.empty(), q2.empty());
    ASSERT_EQ(q1.size(), q2.size());

// PUSH
    for (int i = 0; i < 3; ++i) {
        q1.push(i);
        q2.push(i);
        ASSERT_EQ(q1.back(), q2.back());
        ASSERT_EQ(q1.front(), q2.front());
    }
    ASSERT_QUEUES_EQ(q1, q2);

// EMPTY SIZE 2
    ASSERT_EQ(q1.empty(), q2.empty());
    ASSERT_EQ(q1.size(), q2.size());

// FRONT BACK
    ASSERT_EQ(q1.front(), q2.front());
    ASSERT_EQ(q1.back(), q2.back());

// POP
    for (int i = 0; i < 3; ++i) {
        q1.pop();
        q2.pop();
        ASSERT_EQ(q1.back(), q2.back());
        ASSERT_EQ(q1.front(), q2.front());
    }
    ASSERT_QUEUES_EQ(q1, q2);
}


TEST(Queue, relational_operators)
{
    ft::queue<int> q1;
    ft::queue<int> q2;

    {
        ASSERT_TRUE(q1 == q2);
        ASSERT_EQ(q1.size(), q2.size());

        for (int i = 0; i < 3; ++i) {
            q1.push(i);
            q2.push(i);
            ASSERT_EQ(q1.back(), q2.back());
            ASSERT_EQ(q1.front(), q2.front());
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
