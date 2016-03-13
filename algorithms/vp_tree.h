#ifndef NNCO_VP_TREE_H
#define NNCO_VP_TREE_H


#include <algorithm>
#include <c++/bits/stl_vector.h>
#include "point.h"
#include "vp_node.h"

class VpTree {
public:
    static VpNode *BuildTree(std::vector<Point *> *points);

    static std::pair<int, double> FindDistances(std::vector<Point *> *points, Point *median);

    static int SelectKth(std::vector<Point *> *points, double *distances, int k);

    // TODO func to delete tree recursively
};


#endif //NNCO_VP_TREE_H
