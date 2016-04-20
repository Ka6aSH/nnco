#include <gtest/gtest.h>
#include <point.h>
#include <linear_algorithm.h>

class LinearTest : public ::testing::Test {
private:
    void FreeVec(std::vector<Point *> *vec) {
        for (size_t i = 0; i < vec->size(); ++i)
            delete vec->at(i);
    }

protected:
    void SetUp() {
        points = {
                new Point(2, new double[2]{3, 3}),
                new Point(2, new double[2]{3, 1}),
                new Point(2, new double[2]{1, 3}),
                new Point(2, new double[2]{1, 1}),
                new Point(2, new double[2]{4, 4}),
                new Point(2, new double[2]{4, 0}),
                new Point(2, new double[2]{0, 4}),
                new Point(2, new double[2]{0, 0})
        };
    }

    void TearDown() {
        FreeVec(&points);
    }

    std::vector<Point *> points;
};

TEST_F(LinearTest, insert_delete) {
    LinearAlgorithm alg;
    alg.Init(&points);
    Point query_point(2, new double[2]{-5, -5});
    EXPECT_EQ(points[7], alg.Ann(&query_point));

    alg.RemovePoint(points[7]);
    EXPECT_NE(points[7], alg.Ann(&query_point));

    alg.InsertPoint(points[7]);
    EXPECT_EQ(points[7], alg.Ann(&query_point));
}

TEST_F(LinearTest, contains) {
    LinearAlgorithm alg;
    alg.Init(&points);

    for (int i = 0; i < points.size(); ++i) {
        EXPECT_TRUE(alg.Contains(points[i]));
    }
}

TEST_F(LinearTest, contains_insert_delete) {
    LinearAlgorithm alg;
    alg.Init(&points);

    EXPECT_TRUE(alg.Contains(points[0]));
    alg.RemovePoint(points[0]);
    EXPECT_FALSE(alg.Contains(points[0]));
    Point insert_point(2, new double[2]{50, 50});
    alg.InsertPoint(&insert_point);
    EXPECT_TRUE(alg.Contains(&insert_point));
}

TEST_F(LinearTest, algorithm_sanity) {
    LinearAlgorithm alg;
    alg.Init(&points);
    Point p1(2, new double[2]{2.5, 2.5});
    EXPECT_EQ(points[0], alg.Ann(&p1));
    Point p2(2, new double[2]{-3, -3});
    EXPECT_EQ(points[7], alg.Ann(&p2));
    Point p3(2, new double[2]{0, 2.5});
    EXPECT_EQ(points[2], alg.Ann(&p3));
    Point p4(2, new double[2]{3, 1.9999});
    EXPECT_EQ(points[1], alg.Ann(&p4));
}

