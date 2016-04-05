#ifndef NNCO_KD_TREE_H
#define NNCO_KD_TREE_H


#include <c++/vector>
#include <c++/cstdlib>
#include "kd_node.h"

/**
 * Functions for working with KD-Tree
 */
class KdTree {
public:
    static KdNode *BuildTree(std::vector<Point *> *points, int axis, int dimension);

    static size_t SelectKth(std::vector<Point *> *points, size_t k, int dim);

    static void FreeNodes(KdNode* root);
};


#endif //NNCO_KD_TREE_H
