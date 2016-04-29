#include "aggl_clustering.h"

AgglClustering::AgglClustering(std::vector<Point *> *points,
                               IAlgorithm *algorithm,
                               double (*distance_func)(Point *, Point *),
                               int cluster_number) :
        alg(algorithm), metric(distance_func), cluster_number(cluster_number) {
    AgglClustering::points.insert(AgglClustering::points.begin(), points->begin(), points->end());
}

void AgglClustering::Init() {
    alg->Init(&points);
}

void AgglClustering::RunClustering() {
    std::priority_queue<ClusterTriple, std::vector<ClusterTriple>, CompareClusterTriple> heap;
    std::vector<Cluster *> toDelete;
    for (int i = 0; i < points.size(); ++i) {
        clusters[points[i]] = new Cluster(points[i]);
        Point *nn = alg->Ann(points[i]);
        heap.push({metric(points[i], nn), points[i], nn});
    }
    while (clusters.size() > cluster_number) {
        ClusterTriple ct = heap.top();
        heap.pop();
        if (!alg->Contains(ct.first)) {

        } else if (!alg->Contains(ct.second)) {
            Point *nn = alg->Ann(ct.first);
            heap.push({metric(ct.first, nn), ct.first, nn});
        } else {
            // Remove old clusters
            alg->RemovePoint(ct.first);
            alg->RemovePoint(ct.second);
            // Merge into one
            Cluster *main = clusters[ct.first];
            Cluster *minor = clusters[ct.second];
            Cluster *merged = new Cluster(main, minor);
            clusters[merged->get_center()] = merged;
            // Remove clusters from list
            toDelete.push_back(main);
            toDelete.push_back(minor);
            clusters.erase(ct.first);
            clusters.erase(ct.second);
            // Push it to the algorithm
            alg->InsertPoint(merged->get_center());
            // Find nearest cluster to merged cluster
            Point *nearest = alg->Ann(merged->get_center());
            if (nearest != nullptr)
                heap.push({metric(merged->get_center(), nearest), merged->get_center(), nearest});
        }
    }
    for (int i = 0; i < toDelete.size(); ++i) {
        delete toDelete[i];
    }
}

std::vector<Cluster *> *AgglClustering::GetClusters() {
    auto result = new std::vector<Cluster *>();
    for (auto iter = clusters.begin(); iter != clusters.end(); ++iter) {
        result->push_back(iter->second);
    }
    return result;
}

AgglClustering::~AgglClustering() {
    for (auto iter = clusters.begin(); iter != clusters.end(); ++iter) {
        delete iter->second;
    }
    clusters.clear();
}
