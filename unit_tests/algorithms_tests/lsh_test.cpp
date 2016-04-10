#include <gtest/gtest.h>
#include <lsh_hash_function.h>

TEST(hash_function, near_points) {
    LshHashFunction *func = new LshHashFunction(2);
    Point p1(2, new double[2]{0, 0});
    Point p2(2, new double[2]{0, 0.1});
    Point p3(2, new double[2]{0.05, 0});

    int hash_p1 = func->getHash(&p1);
    int hash_p2 = func->getHash(&p2);
    int hash_p3 = func->getHash(&p3);

    EXPECT_EQ(hash_p1, hash_p2);
    EXPECT_EQ(hash_p1, hash_p3);
    EXPECT_EQ(hash_p2, hash_p3);
}

TEST(hash_function, far_points) {
    LshHashFunction *func = new LshHashFunction(2);
    Point p1(2, new double[2]{0, 0});
    Point p2(2, new double[2]{0, 1});
    Point p3(2, new double[2]{3, 0});

    int hash_p1 = func->getHash(&p1);
    int hash_p2 = func->getHash(&p2);
    int hash_p3 = func->getHash(&p3);

    EXPECT_NE(hash_p1, hash_p2);
    EXPECT_NE(hash_p1, hash_p3);
    EXPECT_NE(hash_p2, hash_p3);
}

