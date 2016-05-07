#include "kd_algorithm.h"

void KdAlgorithm::Init(std::vector<Point *> *points, double (*distance)(Point *, Point *)) {
    if (points == nullptr || points->empty())
        return;
    if (KdAlgorithm::root != nullptr)
        KdTree::FreeNodes(KdAlgorithm::root);
    KdAlgorithm::dimension = points->at(0)->get_dim();
    std::vector<Point *> copy(*points);
    KdAlgorithm::metric = distance;
    KdAlgorithm::root = KdTree::BuildTree(&copy, 0, KdAlgorithm::dimension);
}

Point *KdAlgorithm::Ann(Point *point) {
    std::pair<KdNode *, double> result{nullptr, std::numeric_limits<double>().max()};
    NnsProblem(KdAlgorithm::root, point, &result, 0);
    return result.first->get_point();
}

void KdAlgorithm::NnsProblem(KdNode *root, Point *query, std::pair<KdNode *, double> *best, int axis) {
    if (root == nullptr) {
        return;
    }
    double d = KdAlgorithm::metric(root->get_point(), query);
    Point p_q(1, new double[1]{query->get_coord(axis)});
    Point p_r(1, new double[1]{root->get_coord(axis)});
    double dx = KdAlgorithm::metric(&p_q, &p_r);
    if (!root->is_dead() && root->get_point() != query && (best->first == nullptr || d < best->second)) {
        best->first = root;
        best->second = d;
    }
    axis = (axis + 1) % KdAlgorithm::dimension;
    if (dx > 0) {
        NnsProblem(root->get_left(), query, best, axis);
    } else {
        NnsProblem(root->get_right(), query, best, axis);
    }
    if (dx >= best->second) {
        return;
    }
    if (dx > 0) {
        NnsProblem(root->get_right(), query, best, axis);
    } else {
        NnsProblem(root->get_left(), query, best, axis);
    }
}

void KdAlgorithm::InsertPoint(Point *point) {
    if (root != nullptr) {
        KdTree::InsertPoint(root, point);
    }
}

void KdAlgorithm::RemovePoint(Point *point) {
    KdTree::RemovePoint(root, point);
}


bool KdAlgorithm::Contains(Point *point) {
    return KdTree::Contains(root, point);
}

KdAlgorithm::~KdAlgorithm() {
    KdTree::FreeNodes(KdAlgorithm::root);
}
