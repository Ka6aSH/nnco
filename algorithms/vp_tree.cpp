#include "vp_tree.h"

VpNode *VpTree::BuildTree(std::vector<Point *> *points) {
    if (points->empty()) {
        return nullptr;
    } else {
        if (points->size() == 1) {
            return new VpNode(points->at(0));
        }
    }
    size_t random_idx = std::rand() % points->size();
    std::swap(points->at(random_idx), points->at(0));
    Point *vantage_point = points->at(0);
    std::vector<Point *> other_points(points->begin() + 1, points->end());
    std::pair<int, double> median = VpTree::FindDistances(&other_points, vantage_point);
    std::vector<Point *> inside(other_points.begin(), other_points.begin() + median.first);
    std::vector<Point *> outside(other_points.begin() + median.first, other_points.end());
    return new VpNode(vantage_point,
                      median.second,
                      VpTree::BuildTree(&inside),
                      VpTree::BuildTree(&outside));
}

void VpTree::InsertPoint(VpNode *root, Point *point) {
    double distance = 0;
    VpNode *temp = root;
    VpNode *last = root;

    while (temp != nullptr) {
        last = temp;
        distance = Metrics::GetEuclideanDistance(point, temp->get_point());
        if (temp->get_radius() > distance) {
            temp = temp->get_inside_node();
        } else {
            temp = temp->get_outside_node();
        }
    }

    if (last->get_radius() == 0) {
        last->set_radius(distance);
    }

    if (last->get_radius() > distance) {
        last->set_inside_node(new VpNode(point));
    } else {
        last->set_outside_node(new VpNode(point));
    }
}

void VpTree::RemovePoint(VpNode *root, Point *point) {
    double distance = 0;
    VpNode *temp = root;

    while (temp->get_point() != point) {
        distance = Metrics::GetEuclideanDistance(point, temp->get_point());
        if (temp->get_radius() > distance) {
            temp = temp->get_inside_node();
        } else {
            temp = temp->get_outside_node();
        }
    }

    temp->set_dead(true);
}

std::pair<int, double> VpTree::FindDistances(std::vector<Point *> *points, Point *median) {
    std::unordered_map<Point *, double> distances;
    for (size_t i = 0; i < points->size(); ++i) {
        distances[points->at(i)] = Metrics::GetEuclideanDistance(points->at(i), median);
    }
    std::nth_element(points->begin(), points->begin() + points->size() / 2, points->end(),
                     [&distances](Point *lhs, Point *rhs) {
                         return distances[lhs] < distances[rhs];
                     });
    return std::pair<int, double>{points->size() / 2, distances[points->at(points->size() / 2)]};
}

void VpTree::FreeNodes(VpNode *root) {
    if (root == nullptr)
        return;

    VpTree::FreeNodes(root->get_inside_node());
    VpTree::FreeNodes(root->get_outside_node());

    delete root;
}
