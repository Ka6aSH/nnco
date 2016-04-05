#ifndef NNCO_VP_TREE_H
#define NNCO_VP_TREE_H

#include <c++/cstdlib>
#include <c++/vector>
#include "point.h"
#include "vp_node.h"
#include "metrics.h"

class VpTree {
public:
    static VpNode *BuildTree(std::vector<Point *> *points);

    static std::pair<int, double> FindDistances(std::vector<Point *> *points, Point *median);

    static size_t SelectKth(std::vector<Point *> *points, double *distances, size_t k);

    static void FreeNodes(VpNode* root);
};


#endif //NNCO_VP_TREE_H
