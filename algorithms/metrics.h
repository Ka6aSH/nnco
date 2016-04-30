#ifndef NNCO_METRICS_H
#define NNCO_METRICS_H


#include <cmath>
#include "point.h"

class Metrics {
public:
    static double GetEuclideanDistance(Point *p1, Point *p2);

    static double GetClarkDistance(Point *p1, Point *p2);

    static double GetPenroseDistance(Point *p1, Point *p2);

    static double GetLorentzianDistanceSafe(Point *p1, Point *p2);

    static double GetLorentzianDistanceUnsafe(Point *p1, Point *p2);
};


#endif //NNCO_METRICS_H
