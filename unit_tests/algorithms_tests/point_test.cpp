#include "gtest/gtest.h"
#include "point.h"

TEST(point_dot, sanity) {
    Point p1(2, new double[2]{3, 4});
    Point p2(2, new double[2]{3, 4});
    EXPECT_DOUBLE_EQ(p1.dot(&p2), 25.0);
}

TEST(point_dot, zero_first_op) {
    Point p1(2, new double[2]{0, 4});
    Point p2(2, new double[2]{3, 4});
    EXPECT_DOUBLE_EQ(p1.dot(&p2), 16.0);
}

TEST(point_dot, zero_second_op) {
    Point p1(7, new double[7]{1, 1, 1, 100, 1, 1, 1});
    Point p2(7, new double[7]{1, 1, 1, 0, 1, 1, 1});
    EXPECT_DOUBLE_EQ(p1.dot(&p2), 6.0);
}