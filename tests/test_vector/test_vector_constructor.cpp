//
// Created by airat on 17.01.2021.
//

#include "test_vector.hpp"



TEST(Vector_constructor, vector_default) {
    ft::vector<int> v1;
    std::vector<int> v2;

    ASSERT_VECTORS_EQ(v1, v2);
}

TEST(Vector_constructor, vector_fill) {
    size_t count = 3;
    ft::vector<int> v1(count, 22);
    std::vector<int> v2(count, 22);

    ASSERT_VECTORS_EQ(v1, v2);
}
