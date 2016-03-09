#include "kd_node.h"

bool KdNode::isLeaf() {
    return (left == nullptr) && (right == nullptr);
}

double KdNode::getCoord(int dim) {
    return point->getCoord(dim);
}
