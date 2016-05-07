#ifndef NNCO_METRICS_H
#define NNCO_METRICS_H


#include <cmath>
#include "point.h"

class Metrics {
public:
    static double GetEuclideanDistance(Point *p1, Point *p2);

    static double GetEuclideanDistance(double p1, double p2, int dim);

    static double GetClarkDistance(Point *p1, Point *p2);

    static double GetClarkDistance(double p1, double p2, int dim);

    static double GetPenroseDistance(Point *p1, Point *p2);

    static double GetPenroseDistance(double p1, double p2, int dim);

    static double GetLorentzianDistanceSafe(Point *p1, Point *p2);

    static double GetLorentzianDistanceUnsafe(Point *p1, Point *p2);

    static double GetLorentzianDistance(double p1, double p2, int dim);
};


#endif //NNCO_METRICS_H
