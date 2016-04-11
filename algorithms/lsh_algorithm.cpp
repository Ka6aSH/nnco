#include "lsh_algorithm.h"
#include "metrics.h"

void LshAlgorithm::Init(std::vector<Point *> *points) {
    int d = points->at(0)->get_dim();
    int k = d * 5;
    bucketsNumber = (int) std::round(std::pow(d, 0.25));
    buckets = new LshBucket *[bucketsNumber];
    LshBucket *b;
    for (int i = 0; i < bucketsNumber; i++) {
        b = new LshBucket(k, d);
        for (size_t j = 0; j < points->size(); j++)
            b->addPoint(points->at(j));
        buckets[i] = b;
    }
}

Point *LshAlgorithm::Ann(Point *q) {
    double dist = std::numeric_limits<double>().max();
    double temp_dist = 0;
    Point *res = nullptr;
    std::vector<Point *> *temp_points;
    for (int i = 0; i < bucketsNumber; ++i) {
        auto bucket = buckets[i];
        if ((temp_points = bucket->getPoints(q)) != nullptr) {
            for (auto point = temp_points->begin(); point != temp_points->end(); ++point) {
                temp_dist = Metrics::GetEuclideanDistance(q, *point);
                if (temp_dist < dist) {
                    res = *point;
                    dist = temp_dist;
                }
            }
        }
    }
    return res;
}

LshAlgorithm::~LshAlgorithm() {
    if (buckets != nullptr)
        for (int i = 0; i < bucketsNumber; ++i) {
            delete buckets[i];
        }
    delete buckets;
}
