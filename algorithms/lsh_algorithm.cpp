#include "lsh_algorithm.h"

void LshAlgorithm::Init(std::vector<Point *> *points, double (*distance)(Point *, Point *)) {
    if (buckets != nullptr) {
        for (int i = 0; i < buckets_number; ++i) {
            delete buckets[i];
        }
        delete[] buckets;
    }
    int d = points->at(0)->get_dim();
    if (buckets_number < 1) {
        buckets_number = (int) std::round(std::pow(d, 0.25));
    }
    if (functions_number < 1) {
        functions_number = d * 5;
    }
    buckets = new LshBucket *[buckets_number];
    LshBucket *b;
    for (int i = 0; i < buckets_number; i++) {
        b = new LshBucket(functions_number, d);
        for (size_t j = 0; j < points->size(); j++)
            b->AddPoint(points->at(j));
        buckets[i] = b;
    }
    node_points.clear();
    node_points.insert(node_points.begin(), points->begin(), points->end());
    metric = distance;
}

Point *LshAlgorithm::Ann(Point *q) {
    double dist = std::numeric_limits<double>().max();
    double temp_dist = 0;
    Point *res = nullptr;
    std::vector<Point *> *temp_points;
    for (int i = 0; i < buckets_number; ++i) {
        auto bucket = buckets[i];
        if ((temp_points = bucket->GetPoints(q)) != nullptr) {
            for (auto point = temp_points->begin(); point != temp_points->end(); ++point) {
                if (*point != q) {
                    temp_dist = metric(q, *point);
                    if (temp_dist < dist) {
                        res = *point;
                        dist = temp_dist;
                    }
                }
            }
        }
    }
    if (res == nullptr) {
        if (conservative) {
            for (auto point = node_points.begin(); point != node_points.end(); ++point) {
                if (*point != q) {
                    temp_dist = metric(q, *point);
                    if (temp_dist < dist) {
                        res = *point;
                        dist = temp_dist;
                    }
                }
            }
        } else {
            int idx = rand() % node_points.size();
            while (node_points[idx] == q) {
                idx = rand() % node_points.size();
            }
            return node_points[idx];
        }
    }
    return res;
}

void LshAlgorithm::InsertPoint(Point *point) {
    node_points.push_back(point);
    for (int i = 0; i < buckets_number; i++) {
        buckets[i]->AddPoint(point);
    }
}

void LshAlgorithm::RemovePoint(Point *point) {
    node_points.erase(std::remove(node_points.begin(), node_points.end(), point));
    for (int i = 0; i < buckets_number; i++) {
        buckets[i]->RemovePoint(point);
    }
}

bool LshAlgorithm::Contains(Point *point) {
    for (int i = 0; i < buckets_number; i++) {
        if (buckets[i]->Contains(point)) {
            return true;
        }
    }
    return false;
}

LshAlgorithm::~LshAlgorithm() {
    if (buckets != nullptr)
        for (int i = 0; i < buckets_number; ++i) {
            delete buckets[i];
        }
    delete[] buckets;
}
