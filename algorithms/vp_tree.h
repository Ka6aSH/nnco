#ifndef NNCO_VP_TREE_H
#define NNCO_VP_TREE_H


#include <cstdlib>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include "point.h"
#include "vp_node.h"

class VpTree {
public:
    static VpNode *BuildTree(std::vector<Point *> *points, double (*distance)(Point *p1, Point *p2));

    static void InsertPoint(VpNode *root, Point *point, double (*distance)(Point *p1, Point *p2));

    static void RemovePoint(VpNode *root, Point *point, double (*distance)(Point *p1, Point *p2));

    static std::pair<double, double *> FindDistances(std::vector<Point *> *points, Point *median,
                                                     double (*distance)(Point *p1, Point *p2));

    static void FreeNodes(VpNode *root);

    static bool Contains(VpNode *root, Point *point, double (*distance)(Point *p1, Point *p2));
};


#endif //NNCO_VP_TREE_H
