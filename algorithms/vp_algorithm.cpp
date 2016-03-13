#include "vp_algorithm.h"

void VpAlgorithm::Init(std::vector<Point *> *points) {
    if (points == nullptr || points->empty())
        return;
    if (VpAlgorithm::root != nullptr)
        // TODO memory leak
        delete VpAlgorithm::root;
    std::vector<Point *> copy(*points);
    VpAlgorithm::root = VpTree::BuildTree(&copy);
}

Point *VpAlgorithm::Ann(Point *point) {
    std::pair<VpNode *, double> result{nullptr, -1};
    NnsProblem(VpAlgorithm::root, point, &result);
    return result.first->get_point();
}

void VpAlgorithm::NnsProblem(VpNode *root, Point *q, std::pair<VpNode *, double> *best) {
    if (root == nullptr) {
        return;
    }
    double distance = Metrics::GetEuclideanDistance(root->get_point(), q);
    if (best->first == nullptr || distance < best->second) {
        best->first = root;
        best->second = distance;
    }
    if (root->get_inside_node() == nullptr && root->get_outside_node() == nullptr) {
        return;
    }
    if (distance < root->get_radius()) {
        if (distance - best->second <= root->get_radius()) {
            VpAlgorithm::NnsProblem(root->get_inside_node(), q, best);
        }
        if (distance + best->second >= root->get_radius()) {
            VpAlgorithm::NnsProblem(root->get_outside_node(), q, best);
        }
    } else {
        if (distance + best->second >= root->get_radius()) {
            VpAlgorithm::NnsProblem(root->get_outside_node(), q, best);
        }
        if (distance - best->second <= root->get_radius()) {
            VpAlgorithm::NnsProblem(root->get_inside_node(), q, best);
        }
    }
}

VpAlgorithm::~VpAlgorithm() {
    delete VpAlgorithm::root;
}
