#include "lsh_bucket.h"

LshBucket::LshBucket(int k, int d) {
    function_number = k;
    functions = new LshHashFunction *[k];
    for (int i = 0; i < k; ++i) {
        functions[i] = new LshHashFunction(d);
    }
}

int LshBucket::getHash(Point *p) {
    int hash = 0;
    for (int i = 0; i < function_number; ++i)
        hash = 32 * hash + functions[i]->getHash(p);
    return hash;
}

void LshBucket::addPoint(Point *p) {
    int hash = getHash(p);
    if (!points.count(hash))
        points[hash] = new std::vector<Point *>();
    points[hash]->push_back(p);
}

std::vector<Point *> *LshBucket::getPoints(Point *q) {
    int hash = getHash(q);
    if (!points.count(hash)) {
        return nullptr;
    }
    return points[hash];
}

LshBucket::~LshBucket() {
    for (int i = 0; i < function_number; ++i) {
        delete functions[i];
    }
    delete[] functions;
    for (auto iter = points.begin(); iter != points.end(); iter++) {
        delete iter->second;
    }
    points.clear();
}











