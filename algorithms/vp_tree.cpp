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
    std::pair<double, double *> median = VpTree::FindDistances(&other_points, vantage_point);
    std::vector<Point *> inside;
    std::vector<Point *> outside;
    auto radius = median.first;
    auto distances = median.second;
    for (int i = 0; i < other_points.size(); ++i) {
        if (distances[i] < radius) {
            inside.push_back(other_points[i]);
        } else {
            outside.push_back(other_points[i]);
        }
    }
    delete[] distances;
    return new VpNode(vantage_point,
                      radius,
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

std::pair<double, double *> VpTree::FindDistances(std::vector<Point *> *points, Point *median) {
    std::vector<double> local_distances(points->size());
    double *external_distances = new double[points->size()];
    for (size_t i = 0; i < points->size(); ++i) {
        external_distances[i] = local_distances[i] = Metrics::GetEuclideanDistance(points->at(i), median);
    }
    std::nth_element(local_distances.begin(),
                     local_distances.begin() + local_distances.size() / 2,
                     local_distances.end());
    return std::pair<double, double *>{local_distances[local_distances.size() / 2], external_distances};
}

void VpTree::FreeNodes(VpNode *root) {
    if (root == nullptr)
        return;

    VpTree::FreeNodes(root->get_inside_node());
    VpTree::FreeNodes(root->get_outside_node());

    delete root;
}
