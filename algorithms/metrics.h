#ifndef NNCO_METRICS_H
#define NNCO_METRICS_H


#include <c++/cmath>
#include "point.h"

class Metrics {
public:
    static double GetEuclideanDistance(Point *p1, Point *p2);
};


#endif //NNCO_METRICS_H
