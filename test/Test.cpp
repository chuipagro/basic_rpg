/**
 * @file Test
 * @author chuipagro
 * @brief 
 * @version 0.1
 * @date 12/17/25
 * * @copyright Copyright (c) 2025
 * */

#include <gtest/gtest.h>

TEST(MathTest, BasicCheck) {
    EXPECT_EQ(2 + 2, 4);
}

TEST(PlayerTest, HealthCheck) {
    int hp = 100;
    hp -= 20;
    EXPECT_EQ(hp, 80);
}