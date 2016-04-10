#include <gtest/gtest.h>
#include <lsh_hash_function.h>
#include <lsh_bucket.h>

TEST(lsh_hash_function, near_points) {
    LshHashFunction func(2);
    Point p1(2, new double[2]{0, 0});
    Point p2(2, new double[2]{0, 0.05});
    Point p3(2, new double[2]{0.05, 0});

    int hash_p1 = func.getHash(&p1);
    int hash_p2 = func.getHash(&p2);
    int hash_p3 = func.getHash(&p3);

    EXPECT_EQ(hash_p1, hash_p2);
    EXPECT_EQ(hash_p1, hash_p3);
    EXPECT_EQ(hash_p2, hash_p3);
}

TEST(lsh_hash_function, far_points) {
    LshHashFunction func(2);
    Point p1(2, new double[2]{0, 0});
    Point p2(2, new double[2]{100, 100});
    Point p3(2, new double[2]{75, 75});

    int hash_p1 = func.getHash(&p1);
    int hash_p2 = func.getHash(&p2);
    int hash_p3 = func.getHash(&p3);

    EXPECT_NE(hash_p1, hash_p2);
    EXPECT_NE(hash_p1, hash_p3);
}

TEST(lsh_buckets, sanity) {
    Point p1(2, new double[2]{0, 0});
    LshBucket bucket(1, 2);
    // One point list
    Point p2(2, new double[2]{0, 0.05});
    Point p3(2, new double[2]{0.05, 0});
    bucket.addPoint(&p2);
    bucket.addPoint(&p3);
    // Second point list
    Point p4(2, new double[2]{100, 100});
    Point p5(2, new double[2]{75, 75});
    bucket.addPoint(&p4);
    bucket.addPoint(&p5);

    auto list = bucket.getPoints(&p1);
    EXPECT_EQ(list->size(), 2);
    EXPECT_EQ(list->at(0), &p2);
    EXPECT_EQ(list->at(1), &p3);
}

