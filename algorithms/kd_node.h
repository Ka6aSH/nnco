#ifndef NNCO_KD_NODE_H
#define NNCO_KD_NODE_H


#include "point.h"

/**
 * The class describe the node on KD-tree.
 * Note that this is just a wrapper and DO NOT release any resources
 */
class KdNode {

public:
    KdNode(Point *point, KdNode *left = nullptr, KdNode *right = nullptr)
            : point(point), left(left), right(right) { }

    bool isLeaf();

    double getCoord(int dim);

    Point *getPoint() const { return point; }

    KdNode *getLeft() const { return left; }

    void setLeft(KdNode *left) { KdNode::left = left; }

    KdNode *getRight() const { return right; }

    void setRight(KdNode *right) { KdNode::right = right; }

private:
    Point *point;
    KdNode *left;
    KdNode *right;
};


#endif //NNCO_KD_NODE_H
