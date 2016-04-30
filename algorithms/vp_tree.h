#ifndef NNCO_VP_TREE_H
#define NNCO_VP_TREE_H


#include <cstdlib>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include "point.h"
#include "vp_node.h"
#include "metrics.h"

class VpTree {
public:
    static VpNode *BuildTree(std::vector<Point *> *points);

    static void InsertPoint(VpNode *root, Point *point);

    static void RemovePoint(VpNode *root, Point *point);

    static std::pair<double, double *> FindDistances(std::vector<Point *> *points, Point *median);

    static void FreeNodes(VpNode *root);

    static bool Contains(VpNode *root, Point *point);
};


#endif //NNCO_VP_TREE_H
