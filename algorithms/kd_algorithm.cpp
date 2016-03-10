#include "kd_algorithm.h"

void KdAlgorithm::init(std::vector<Point *> *points) {
    if (points == nullptr || points->empty())
        return;
    if (KdAlgorithm::root != nullptr)
        delete KdAlgorithm::root;
    KdAlgorithm::dimension =points->at(0)->getDimension();
    KdAlgorithm::root = KdTree::buildTree(new std::vector<Point*>(*points), 0, KdAlgorithm::dimension);
}

Point *KdAlgorithm::Ann(Point *point) {
    std::pair<KdNode*, double> result{nullptr, -1};
    nnsProblem(KdAlgorithm::root, point, &result, 0);
    return result.first->getPoint();
}

void KdAlgorithm::nnsProblem(KdNode* root, Point *query, std::pair<KdNode *, double>* best, int axis) {
    if (root == nullptr) {
        return;
    }
    double d = Metrics::euclidean_distance(root->getPoint(), query);
    double dx = root->getCoord(axis) - query->getCoord(axis);
    double dx2 = dx * dx;
    if (best->first == nullptr || d < best->second) {
        best->first = root;
        best->second = d;
    }
    axis = (axis + 1) % KdAlgorithm::dimension;
    if (dx > 0) {
        nnsProblem(root->getLeft(), query, best, axis);
    } else {
        nnsProblem(root->getRight(), query, best, axis);
    }
    if (dx2 >= best->second) {
        return;
    }
    if (dx > 0) {
        nnsProblem(root->getRight(), query, best, axis);
    } else {
        nnsProblem(root->getLeft(), query, best, axis);
    }
}

KdAlgorithm::~KdAlgorithm() {
    delete KdAlgorithm::root;
}
