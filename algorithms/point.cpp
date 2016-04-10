#include "point.h"

double Point::Dot(const Point *point) const {
    double res = 0;
    double *another_vector = point->vector;
    for (int i = 0; i < dimension; ++i) {
        res += vector[i] * another_vector[i];
    }
    return res;
}

double Point::get_coord(int dim) {
    return vector[dim % dimension];
}

Point::~Point(void) {
    delete[] vector;
}
