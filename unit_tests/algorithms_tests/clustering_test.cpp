#include <gtest/gtest.h>
#include <point.h>
#include <aggl_clustering.h>
#include <linear_algorithm.h>

TEST(clustering, sanity) {
    std::vector<Point *> points{new Point(2, new double[2]{1, 3}),
                                new Point(2, new double[2]{1, 4}),
                                new Point(2, new double[2]{3, 3}),
                                new Point(2, new double[2]{3, 4}),
                                new Point(2, new double[2]{5, 1}),
                                new Point(2, new double[2]{5, 2}),
                                new Point(2, new double[2]{6, 3}),
                                new Point(2, new double[2]{3.5, 5}),
                                new Point(2, new double[2]{0, 2})};
    IAlgorithm *algorithm = new LinearAlgorithm();
    AgglClustering clustering(&points, algorithm, Metrics::GetEuclideanDistance, 3);
    clustering.Init();
    clustering.RunClustering();
    auto result = clustering.GetClusters();

    EXPECT_EQ(result->size(), 3);
    for (auto iter = result->begin(); iter != result->end(); ++iter) {
        EXPECT_EQ((*iter)->get_points()->size(), 3);
    }


    delete result;
    delete algorithm;
    for (int i = 0; i < points.size(); ++i)
        delete points[i];
}

