#include "kd_node.h"

bool KdNode::is_leaf() {
    return (left == nullptr) && (right == nullptr);
}

double KdNode::get_coord(int dim) {
    return point->get_coord(dim);
}
