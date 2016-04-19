#include <gtest/gtest.h>
#include <point.h>
#include <cluster.h>

class ClusterTest : public ::testing::Test {
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

TEST_F(ClusterTest, initializing
) {
    Cluster cluster(&points);
    EXPECT_DOUBLE_EQ(cluster
                             .

                                     get_center()->

            get_coord(0), 2);
    EXPECT_DOUBLE_EQ(cluster
                             .

                                     get_center()->

            get_coord(1), 2);
}

TEST_F(ClusterTest, merging
) {
    auto first_cluster = new std::vector<Point *>(points.begin(), points.begin() + points.size() / 2);
    auto second_cluster = new std::vector<Point *>(points.begin() + points.size() / 2, points.end());
    Point p1(2, new double[2]{1, 2});
    Point p2(2, new double[2]{3, 2});
    Cluster cluster1(first_cluster);
    cluster1.
            AddPoint(&p1);
    Cluster cluster2(second_cluster);
    cluster2.
            AddPoint(&p2);
    EXPECT_LT(cluster1
                      .

                              get_center()->

            get_coord(0), 2);
    EXPECT_DOUBLE_EQ(cluster1
                             .

                                     get_center()->

            get_coord(1), 2);
    EXPECT_GT(cluster2
                      .

                              get_center()->

            get_coord(0), 2);
    EXPECT_DOUBLE_EQ(cluster2
                             .

                                     get_center()->

            get_coord(1), 2);
    cluster1.
            AddCluster(&cluster2);
    EXPECT_DOUBLE_EQ(cluster1
                             .

                                     get_center()->

            get_coord(0), 2);
    EXPECT_DOUBLE_EQ(cluster1
                             .

                                     get_center()->

            get_coord(1), 2);
}

