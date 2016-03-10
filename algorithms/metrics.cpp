#include "metrics.h"

double Metrics::GetEuclideanDistance(Point *p1, Point *p2) {
    double res = 0;
    double *vec1 = p1->get_vec();
    double *vec2 = p2->get_vec();
    for (int i = 0; i < p1->get_dim(); ++i)
        res += (vec1[i] - vec2[i]) * (vec1[i] - vec2[i]);
    return std::sqrt(res);
}
