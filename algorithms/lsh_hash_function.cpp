#include "lsh_hash_function.h"

LshHashFunction::LshHashFunction(int dimension) {
    double *temp = new double[dimension];
    std::default_random_engine generator(rand());
    std::normal_distribution<double> distribution_norm(0, 1);
    std::uniform_real_distribution<double> distribution_uni(0.0, 1.0);

    for (int i = 0; i < dimension; ++i) {
        temp[i] = distribution_norm(generator);
    }
    a = new Point(dimension, temp);
    b = distribution_uni(generator) * w;
}

int LshHashFunction::getHash(const Point *point) {
    return (int) ((a->Dot(point) + b) / w);
}

LshHashFunction::~LshHashFunction() {
    delete a;
}





