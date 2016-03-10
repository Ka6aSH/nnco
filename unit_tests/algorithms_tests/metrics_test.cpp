#include <gtest/gtest.h>
#include <point.h>
#include <metrics.h>

TEST(metrics, euclidian_sanity) {
    Point p1(2, new double[2]{1, 2});
    Point p2(2, new double[2]{1, 2});
    EXPECT_DOUBLE_EQ(Metrics::euclidean_distance(&p1, &p2), 0);
    Point p3(2, new double[2]{2, 0});
    Point p4(2, new double[2]{0, 0});
    EXPECT_DOUBLE_EQ(Metrics::euclidean_distance(&p3, &p4), 2);
}

TEST(metrics, euclidian_commutative) {
    Point p1(5, new double[5]{5, 7, 3, 2, 1});
    Point p2(5, new double[5]{6, 9, 2, 5, 1});
    EXPECT_DOUBLE_EQ(Metrics::euclidean_distance(&p1, &p2),
                     Metrics::euclidean_distance(&p2, &p1));
}