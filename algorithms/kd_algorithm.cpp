#include "kd_algorithm.h"

void KdAlgorithm::Init(std::vector<Point *> *points) {
    if (points == nullptr || points->empty())
        return;
    if (KdAlgorithm::root != nullptr)
        delete KdAlgorithm::root;
    KdAlgorithm::dimension = points->at(0)->get_dim();
    KdAlgorithm::root = KdTree::BuildTree(new std::vector<Point *>(*points), 0, KdAlgorithm::dimension);
}

Point *KdAlgorithm::Ann(Point *point) {
    std::pair<KdNode *, double> result{nullptr, -1};
    nnsProblem(KdAlgorithm::root, point, &result, 0);
    return result.first->get_point();
}

void KdAlgorithm::nnsProblem(KdNode *root, Point *query, std::pair<KdNode *, double> *best, int axis) {
    if (root == nullptr) {
        return;
    }
    double d = Metrics::GetEuclideanDistance(root->get_point(), query);
    double dx = root->get_coord(axis) - query->get_coord(axis);
    double dx2 = dx * dx;
    if (best->first == nullptr || d < best->second) {
        best->first = root;
        best->second = d;
    }
    axis = (axis + 1) % KdAlgorithm::dimension;
    if (dx > 0) {
        nnsProblem(root->get_left(), query, best, axis);
    } else {
        nnsProblem(root->get_right(), query, best, axis);
    }
    if (dx2 >= best->second) {
        return;
    }
    if (dx > 0) {
        nnsProblem(root->get_right(), query, best, axis);
    } else {
        nnsProblem(root->get_left(), query, best, axis);
    }
}

KdAlgorithm::~KdAlgorithm() {
    delete KdAlgorithm::root;
}
