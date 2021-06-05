//
// Created by airat on 16.01.2021.
//

#include <gtest/gtest.h>
#include <map>
int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    std::map<int, int> mm;
    return RUN_ALL_TESTS();
}