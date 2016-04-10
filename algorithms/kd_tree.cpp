#include "kd_tree.h"

KdNode *KdTree::BuildTree(std::vector<Point *> *points, int axis, int dimension) {
    if (points->empty()) {
        return nullptr;
    } else {
        if (points->size() == 1) {
            return new KdNode(points->at(0));
        }
    }
    size_t median_index = points->size() / 2;
    std::nth_element(points->begin(), points->begin() + median_index, points->end(),
                     [&axis](Point *lhs, Point *rhs) {
                         return lhs->get_coord(axis) < rhs->get_coord(axis);
                     });
    int next_axis = (axis + 1) % dimension;
    std::vector<Point *> left_list(points->begin(), points->begin() + median_index);
    std::vector<Point *> right_list(points->begin() + median_index + 1, points->end());
    auto result_node = new KdNode(points->at(median_index),
                                  BuildTree(&left_list, next_axis, dimension),
                                  BuildTree(&right_list, next_axis, dimension));
    return result_node;
}

void KdTree::FreeNodes(KdNode *root) {
    if (root == nullptr)
        return;

    KdTree::FreeNodes(root->get_left());
    KdTree::FreeNodes(root->get_right());

    delete root;
}

