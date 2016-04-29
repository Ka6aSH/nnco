#ifndef NNCO_AGGL_CLUSTERING_H
#define NNCO_AGGL_CLUSTERING_H


#include <c++/queue>
#include <c++/algorithm>
#include <c++/unordered_map>
#include "ialgorithm.h"
#include "cluster.h"

struct ClusterTriple {
    double dist;
    Point *first;
    Point *second;
};

class CompareClusterTriple {
public:
    bool operator()(ClusterTriple &t1, ClusterTriple &t2) {
        return t1.dist > t2.dist;
    }
};

class AgglClustering {
public:
    AgglClustering(std::vector<Point *> *points,
                   IAlgorithm *alg,
                   double (*distance_func)(Point *, Point *),
                   int cluster_number);

    void Init();

    void RunClustering();

    std::vector<Cluster *> *GetClusters();

    virtual ~AgglClustering();

private:
    int cluster_number;
    IAlgorithm *alg;
    std::vector<Point *> points;
    std::unordered_map<Point *, Cluster *> clusters;

    double (*metric)(Point *lhs, Point *rhs);
};


#endif //NNCO_AGGL_CLUSTERING_H
