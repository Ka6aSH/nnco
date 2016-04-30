#include "metrics.h"

double Metrics::GetEuclideanDistance(Point *p1, Point *p2) {
    double res = 0;
    double *vec1 = p1->get_vec();
    double *vec2 = p2->get_vec();
    for (int i = 0; i < p1->get_dim(); ++i)
        res += (vec1[i] - vec2[i]) * (vec1[i] - vec2[i]);
    return std::sqrt(res);
}

double Metrics::GetClarkDistance(Point *p1, Point *p2) {
    double res = 0;
    double *vec1 = p1->get_vec();
    double *vec2 = p2->get_vec();
    for (int i = 0; i < p1->get_dim(); ++i) {
        if (vec1[i] == 0 && vec2[i] == 0) continue;
        double temp = (vec1[i] - vec2[i]) / (std::abs(vec1[i]) + std::abs(vec2[i]));
        res += temp * temp;
    }
    return std::sqrt(res / p1->get_dim());
}

double Metrics::GetPenroseDistance(Point *p1, Point *p2) {
    double res = 0;
    double *vec1 = p1->get_vec();
    double *vec2 = p2->get_vec();
    for (int i = 0; i < p1->get_dim(); ++i) {
        res += std::abs(vec1[i] - vec2[i]);
    }
    return res * std::sqrt(p1->get_dim());
}

double Metrics::GetLorentzianDistanceSafe(Point *p1, Point *p2) {
    double res = 0;
    double *vec1 = p1->get_vec();
    double *vec2 = p2->get_vec();
    for (int i = 0; i < p1->get_dim(); ++i) {
        res += std::log(1 + std::abs(vec1[i] - vec2[i]));
    }
    return res;
}

double Metrics::GetLorentzianDistanceUnsafe(Point *p1, Point *p2) {
    double res = 1;
    double *vec1 = p1->get_vec();
    double *vec2 = p2->get_vec();
    for (int i = 0; i < p1->get_dim(); ++i) {
        res *= 1 + std::abs(vec1[i] - vec2[i]);
    }
    return std::log(res);
}
