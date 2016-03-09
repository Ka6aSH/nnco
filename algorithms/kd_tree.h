#ifndef NNCO_KD_TREE_H
#define NNCO_KD_TREE_H


#include <algorithm>
#include <c++/bits/stl_vector.h>
#include "kd_node.h"

/**
 * Functions for working with KD-Tree
 */
class KdTree {
public:
    static KdNode *buildTree(std::vector<Point *> *points, int axis, int dimension);

    static int selectKth(std::vector<Point *> *points, int k, int dim);
};


#endif //NNCO_KD_TREE_H
