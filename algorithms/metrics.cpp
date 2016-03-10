#include "metrics.h"

double Metrics::euclidean_distance(Point *p1, Point *p2) {
    double res = 0;
    double *vec1 = p1->getVector();
    double *vec2 = p2->getVector();
    for (int i = 0; i < p1->getDimension(); ++i)
        res += (vec1[i] - vec2[i]) * (vec1[i] - vec2[i]);
    return std::sqrt(res);
}
