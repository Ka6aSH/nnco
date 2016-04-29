#include "linear_algorithm.h"

void LinearAlgorithm::Init(std::vector<Point *> *points) {
    if (LinearAlgorithm::points != nullptr) {
        delete points;
    }
    LinearAlgorithm::points = new std::vector<Point *>(points->begin(), points->end());
}

Point *LinearAlgorithm::Ann(Point *q) {
    double distance = std::numeric_limits<double>().max();
    Point *result = nullptr;
    for (size_t i = 0; i < points->size(); ++i) {
        if (points->at(i) != q) {
            double temp_distance = Metrics::GetEuclideanDistance(q, points->at(i));
            if (temp_distance < distance) {
                distance = temp_distance;
                result = points->at(i);
            }
        }
    }
    return result;
}

void LinearAlgorithm::InsertPoint(Point *point) {
    LinearAlgorithm::points->push_back(point);
}

void LinearAlgorithm::RemovePoint(Point *point) {
    points->erase(std::remove(points->begin(), points->end(), point));
}

bool LinearAlgorithm::Contains(Point *point) {
    for (size_t i = 0; i < points->size(); ++i) {
        if (points->at(i) == point) {
            return true;
        }
    }
    return false;
}

LinearAlgorithm::~LinearAlgorithm() {
    delete points;
}






