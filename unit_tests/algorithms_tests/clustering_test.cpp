#include <gtest/gtest.h>
#include <point.h>
#include <aggl_clustering.h>
#include <linear_algorithm.h>
#include <cluster_quality.h>

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

TEST(clustering_quality, internal) {
    std::vector<Point *> points_first{new Point(2, new double[2]{0, 1}),
                                      new Point(2, new double[2]{2, 1}),
                                      new Point(2, new double[2]{1, 2}),
                                      new Point(2, new double[2]{1, 0})};
    std::vector<Point *> points_second{new Point(2, new double[2]{0, 0}),
                                       new Point(2, new double[2]{2, 0}),
                                       new Point(2, new double[2]{2, 2}),
                                       new Point(2, new double[2]{2, 0})};
    IAlgorithm *algorithm = new LinearAlgorithm();
    AgglClustering clustering1(&points_first, algorithm, Metrics::GetEuclideanDistance, 1);
    clustering1.Init();
    clustering1.RunClustering();
    AgglClustering clustering2(&points_second, algorithm, Metrics::GetEuclideanDistance, 1);
    clustering2.Init();
    clustering2.RunClustering();
    auto result_cluster_1 = clustering1.GetClusters();
    auto result_cluster_2 = clustering2.GetClusters();
    EXPECT_LT(ClusterQuality::CalculateInsideQuality(result_cluster_1),
              ClusterQuality::CalculateInsideQuality(result_cluster_2));

    delete result_cluster_1;
    delete result_cluster_2;
    delete algorithm;
    for (int i = 0; i < points_first.size(); ++i) {
        delete points_first[i];
        delete points_second[i];
    }
}

TEST(clustering_quality, external) {
    std::vector<Point *> points_first{new Point(2, new double[2]{0, 1}),
                                      new Point(2, new double[2]{2, 1}),
                                      new Point(2, new double[2]{1, 2}),
                                      new Point(2, new double[2]{1, 0})};
    std::vector<Point *> points_second{new Point(2, new double[2]{0, 0}),
                                       new Point(2, new double[2]{2, 0}),
                                       new Point(2, new double[2]{2, 2}),
                                       new Point(2, new double[2]{2, 0})};
    IAlgorithm *algorithm = new LinearAlgorithm();
    AgglClustering clustering1(&points_first, algorithm, Metrics::GetEuclideanDistance, 4);
    clustering1.Init();
    clustering1.RunClustering();
    AgglClustering clustering2(&points_second, algorithm, Metrics::GetEuclideanDistance, 4);
    clustering2.Init();
    clustering2.RunClustering();
    auto result_cluster_1 = clustering1.GetClusters();
    auto result_cluster_2 = clustering2.GetClusters();
    EXPECT_LT(ClusterQuality::CalculateOutsideQuality(result_cluster_1),
              ClusterQuality::CalculateOutsideQuality(result_cluster_2));

    delete result_cluster_1;
    delete result_cluster_2;
    delete algorithm;
    for (int i = 0; i < points_first.size(); ++i) {
        delete points_first[i];
        delete points_second[i];
    }
}

