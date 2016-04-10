#ifndef NNCO_LSH_HASH_FUNCTION_H
#define NNCO_LSH_HASH_FUNCTION_H


#include <c++/random>
#include "point.h"

class LshHashFunction {
public:
    LshHashFunction(int dimension);

    int getHash(const Point *point);

    ~LshHashFunction();

private:
    double w = 4;
    Point *a;
    double b;
};


#endif //NNCO_LSH_HASH_FUNCTION_H
