#include "kd_tree.h"

KdNode *KdTree::BuildTree(std::vector<Point *> *points, int axis, int dimension) {
    if (points->empty()) {
        return nullptr;
    } else {
        if (points->size() == 1) {
            return new KdNode(points->at(0));
        }
    }
    int median_index = SelectKth(points, (int) (points->size() / 2), axis);
    int next_axis = (axis + 1) % dimension;
    std::vector<Point*> left_list(points->begin(), points->begin() + median_index);
    std::vector<Point*> right_list(points->begin() + median_index + 1, points->end());
    auto result_node = new KdNode(points->at(median_index),
                                  BuildTree(&left_list, next_axis, dimension),
                                  BuildTree(&right_list, next_axis, dimension));
    return result_node;
}

int KdTree::SelectKth(std::vector<Point *> *points, int k, int dim) {
    int from = 0;
    int to = points->size() - 1;
    int r;
    int w;
    double mid;
    while (from < to) {
        // init
        r = from;
        w = to;
        mid = points->at((r + w) / 2)->get_coord(dim);

        while (r < w) {
            if (points->at(r)->get_coord(dim) >= mid) {
                std::swap(points->at(w), points->at(r));
                w--;
            } else {
                r++;
            }
        }

        if (points->at(r)->get_coord(dim) > mid) {
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
