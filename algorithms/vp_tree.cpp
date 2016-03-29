#include "vp_tree.h"

VpNode *VpTree::BuildTree(std::vector<Point *> *points) {
    if (points->empty()) {
        return nullptr;
    } else {
        if (points->size() == 1) {
            return new VpNode(points->at(0));
        }
    }
    int random_idx = std::rand() % points->size();
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

int VpTree::SelectKth(std::vector<Point *> *points, double *distances, int k) {
    int from = 0;
    int to = points->size() - 1;
    int r;
    int w;
    double mid;
    while (from < to) {
        // init
        r = from;
        w = to;
        mid = distances[(r + w) / 2];

        while (r < w) {
            if (distances[r] >= mid) {
                std::swap(points->at(w), points->at(r));
                std::swap(distances[w], distances[r]);
                w--;
            } else {
                r++;
            }
        }

        if (distances[r] > mid) {
            r--;
        }
        if (k <= r) {
            to = r;
        } else {
            from = r + 1;
        }
    }
    return k;
}

std::pair<int, double> VpTree::FindDistances(std::vector<Point *> *points, Point *median) {
    double distances[points->size()];
    for (int i = 0; i < points->size(); ++i) {
        distances[i] = Metrics::GetEuclideanDistance(points->at(i), median);
    }
    int kth_idx = VpTree::SelectKth(points, distances, points->size() / 2);
    return std::pair<int, double>{kth_idx, distances[kth_idx]};
}

void VpTree::FreeNodes(VpNode *root) {
    if (root == nullptr)
        return;

    VpTree::FreeNodes(root->get_inside_node());
    VpTree::FreeNodes(root->get_outside_node());

    delete root;
}
