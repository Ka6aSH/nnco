#ifndef NNCO_CLUSTER_H
#define NNCO_CLUSTER_H


#include <c++/vector>
#include "point.h"

class Cluster {
public:

    Cluster(std::vector<Point *> *points);

    void AddCluster(Cluster *another);

    void AddPoint(Point *point);

    Point *get_center() const { return center; }

    ~Cluster();

private:
    std::vector<Point *> points;
    Point *center;
    int dimension;

    void CalculateCenter();
};


#endif //NNCO_CLUSTER_H
