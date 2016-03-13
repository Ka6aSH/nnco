#ifndef NNCO_METRICS_H
#define NNCO_METRICS_H


#include "point.h"
#include <c++/cmath>

class Metrics {
public:
    static double GetEuclideanDistance(Point *p1, Point *p2);
};


#endif //NNCO_METRICS_H