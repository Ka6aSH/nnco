#ifndef NNCO_KD_TREE_H
#define NNCO_KD_TREE_H


#include <c++/vector>
#include <c++/cstdlib>
#include <c++/algorithm>
#include "kd_node.h"

/**
 * Functions for working with KD-Tree
 */
class KdTree {
public:
    static KdNode *BuildTree(std::vector<Point *> *points, int axis, int dimension);

    static void InsertPoint(KdNode *root, Point *point);

    static void RemovePoint(KdNode *root, Point *point);

    static bool Contains(KdNode *node, Point *point);

    static void FreeNodes(KdNode *root);

//private:
//    static Point *FindMin(KdNode *node, int cutting_axis, int current_axis);

//    static Point *MinFunction(Point *p1, Point *p2, Point *p3, int dim);

//    static Point *MaxFunction(Point *p1, Point *p2, Point *p3, int dim);
};


#endif //NNCO_KD_TREE_H
