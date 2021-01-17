//
// Created by airat on 17.01.2021.
//

#include "test_queue.hpp"

TEST(Queue_constructor, queue) {
ft::queue<int> q1;
std::queue<int, std::list<int> > q2;

ASSERT_QUEUES_EQ(q1, q2);

}
