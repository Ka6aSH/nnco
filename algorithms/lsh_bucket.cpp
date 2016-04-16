#include "lsh_bucket.h"

LshBucket::LshBucket(int k, int d) {
    function_number = k;
    functions = new LshHashFunction *[k];
    for (int i = 0; i < k; ++i) {
        functions[i] = new LshHashFunction(d);
    }
}

int LshBucket::GetHash(Point *p) {
    int hash = 0;
    for (int i = 0; i < function_number; ++i)
        hash = 32 * hash + functions[i]->getHash(p);
    return hash;
}

void LshBucket::AddPoint(Point *p) {
    int hash = GetHash(p);
    if (!points.count(hash))
        points[hash] = new std::vector<Point *>();
    points[hash]->push_back(p);
}

void LshBucket::RemovePoint(Point *p) {
    int hash = GetHash(p);
    if (points.count(hash)) {
        auto similar_points = points[hash];
        similar_points->erase(std::remove(similar_points->begin(), similar_points->end(), p));
    }
}

std::vector<Point *> *LshBucket::GetPoints(Point *q) {
    int hash = GetHash(q);
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
