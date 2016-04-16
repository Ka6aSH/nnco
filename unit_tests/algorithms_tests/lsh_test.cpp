#include <gtest/gtest.h>
#include <lsh_hash_function.h>
#include <lsh_bucket.h>
#include <lsh_algorithm.h>

TEST(lsh_hash_function, near_points) {
    srand(time(NULL));
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
    srand(time(NULL));
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
    srand(time(NULL));
    Point p1(2, new double[2]{0, 0});
    LshBucket bucket(1, 2);
    // One point list
    Point p2(2, new double[2]{0, 0.05});
    Point p3(2, new double[2]{0.05, 0});
    bucket.AddPoint(&p2);
    bucket.AddPoint(&p3);
    // Second point list
    Point p4(2, new double[2]{100, 100});
    Point p5(2, new double[2]{75, 75});
    bucket.AddPoint(&p4);
    bucket.AddPoint(&p5);

    auto list = bucket.GetPoints(&p1);
    EXPECT_EQ(list->size(), 2);
    EXPECT_EQ(list->at(0), &p2);
    EXPECT_EQ(list->at(1), &p3);
}

TEST(lsh_algorithm, sanity) {
    srand(time(NULL));
    std::vector<Point *> v{new Point(2, new double[2]{1, 1}),
                           new Point(2, new double[2]{1, -1}),
                           new Point(2, new double[2]{-1, 1}),
                           new Point(2, new double[2]{-1, -1}),
                           new Point(2, new double[2]{2, 2}),
                           new Point(2, new double[2]{2, -2}),
                           new Point(2, new double[2]{-2, 2}),
                           new Point(2, new double[2]{-2, -2})};
    LshAlgorithm alg(10, 3);
    alg.Init(&v);
    Point p1(2, new double[2]{0.5, 0.5});
    EXPECT_EQ(v.at(0), alg.Ann(&p1));
    Point p2(2, new double[2]{-5, -5});
    EXPECT_EQ(v.at(7), alg.Ann(&p2));
    Point p3(2, new double[2]{-2, 0.5});
    EXPECT_EQ(v.at(2), alg.Ann(&p3));
    Point p4(2, new double[2]{1, -0.0001});
    EXPECT_EQ(v.at(1), alg.Ann(&p4));

    for (int i = 0; i < v.size(); ++i)
        delete v[i];
}

TEST(lsh_algorithm, insert_delete) {
    srand(time(NULL));
    // Test are combined, because inserting using in basic case with ctor
    std::vector<Point *> v{new Point(2, new double[2]{1, 1}),
                           new Point(2, new double[2]{1, -1}),
                           new Point(2, new double[2]{-1, 1}),
                           new Point(2, new double[2]{-1, -1}),
                           new Point(2, new double[2]{2, 2}),
                           new Point(2, new double[2]{2, -2}),
                           new Point(2, new double[2]{-2, 2}),
                           new Point(2, new double[2]{-2, -2})};
    LshAlgorithm alg(10, 3);
    alg.Init(&v);
    Point query_point(2, new double[2]{-5, -5});
    EXPECT_EQ(v.at(7), alg.Ann(&query_point));

    alg.RemovePoint(v.at(7));
    EXPECT_NE(v.at(7), alg.Ann(&query_point));

    alg.InsertPoint(v.at(7));
    EXPECT_EQ(v.at(7), alg.Ann(&query_point));
}
