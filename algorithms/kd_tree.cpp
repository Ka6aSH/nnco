#include "kd_tree.h"

KdNode *KdTree::buildTree(std::vector<Point *> *points, int axis, int dimension) {
    if (points->empty()) {
        return nullptr;
    } else {
        if (points->size() == 1) {
            return new KdNode(points->at(0));
        }
    }
    int medianIndex = selectKth(points, (int) (points->size() / 2), axis);
    int nextAxis = (axis + 1) % dimension;
    std::vector<Point*> left_list(points->begin(), points->begin() + medianIndex);
    std::vector<Point*> right_list(points->begin() + medianIndex + 1, points->end());
    auto result_node = new KdNode(points->at(medianIndex),
                      buildTree(&left_list, nextAxis, dimension),
                      buildTree(&right_list, nextAxis, dimension));
    return result_node;
}

int KdTree::selectKth(std::vector<Point *> *points, int k, int dim) {
    int from = 0;
    int to = points->size() - 1;
    int r;
    int w;
    double mid;
    while (from < to) {
        // init
        r = from;
        w = to;
        mid = points->at((r + w) / 2)->getCoord(dim);

        while (r < w) {
            if (points->at(r)->getCoord(dim) >= mid) {
                std::swap(points->at(w), points->at(r));
                w--;
            } else {
                r++;
            }
        }

        if (points->at(r)->getCoord(dim) > mid) {
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
