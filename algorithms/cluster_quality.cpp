#include "cluster_quality.h"
#include "metrics.h"

double ClusterQuality::quality = 0;
double ClusterQuality::insert_quality = 0;
double ClusterQuality::outside_quality = 0;

double ClusterQuality::CalculateQuality(std::vector<Cluster *> *clusters) {
    CalculateInsideQuality(clusters);
    CalculateOutsideQuality(clusters);
    ClusterQuality::quality = insert_quality / outside_quality;
    return ClusterQuality::quality;
}

double ClusterQuality::CalculateInsideQuality(std::vector<Cluster *> *clusters) {
    double sum = 0;
    double count = 0;
    for (auto cluster_iter = clusters->begin(); cluster_iter != clusters->end(); ++cluster_iter) {
        Cluster *cluster = *cluster_iter;
        std::vector<Point *> *points = cluster->get_points();
        count += points->size();
        for (auto point_iter = points->begin(); point_iter != points->end(); ++point_iter) {
            sum += Metrics::GetEuclideanDistance(cluster->get_center(), *point_iter);
        }
    }
    ClusterQuality::insert_quality = sum / count;
    return ClusterQuality::insert_quality;
}

double ClusterQuality::CalculateOutsideQuality(std::vector<Cluster *> *clusters) {
    double sum = 0;
    size_t count = clusters->size() * (clusters->size() - 1) / 2;
    for (auto cluster_external = clusters->begin(); cluster_external != clusters->end(); ++cluster_external) {
        for (auto cluster_internal = clusters->begin(); cluster_internal != clusters->end(); ++cluster_internal) {
            sum += Metrics::GetEuclideanDistance((*cluster_external)->get_center(), (*cluster_internal)->get_center());
        }
    }
    ClusterQuality::outside_quality = sum / count;
    return ClusterQuality::outside_quality;
}





