#ifndef NNCO_CLUSTER_H
#define NNCO_CLUSTER_H


#include <vector>
#include "point.h"

class Cluster {
public:

    Cluster(std::vector<Point *> *points);

    Cluster(Point *point);

    Cluster(Cluster *lhs, Cluster *rhs);

    void AddCluster(Cluster *another);

    void AddPoint(Point *point);

    Point *get_center() const { return center; }

    std::vector<Point *> *get_points() { return &points; }

    ~Cluster();

private:
    std::vector<Point *> points;
    Point *center;
    int dimension;

    void CalculateCenter();
};


#endif //NNCO_CLUSTER_H
