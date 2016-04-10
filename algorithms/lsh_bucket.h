#ifndef NNCO_LSH_BUCKET_H
#define NNCO_LSH_BUCKET_H


#include <c++/vector>
#include <c++/map>
#include <c++/algorithm>
#include <c++/unordered_map>
#include "point.h"
#include "lsh_hash_function.h"

class LshBucket {
public:
    LshBucket(int k, int d);

    int getHash(Point *p);

    void addPoint(Point *p);

    std::vector<Point *> *getPoints(Point *q);

    ~LshBucket();

private:
    int function_number;
    LshHashFunction **functions;
    std::unordered_map<int, std::vector<Point *> *> points;
};


#endif //NNCO_LSH_BUCKET_H
