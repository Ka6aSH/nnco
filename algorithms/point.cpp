#include "point.h"

Point::Point(int dim, double *vector) : dimension(dim), vector(vector) {
}

double Point::dot(const Point *point) const {
    double res = 0;
    double* another_vector =  point->vector;
    for (int i = 0; i < dimension; ++i) {
        res += vector[i] * another_vector[i];
    }
    return res;
}

Point::~Point(void) {
    delete[] vector;
}
