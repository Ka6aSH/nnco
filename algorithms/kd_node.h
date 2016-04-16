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
            : point(point), left(left), right(right), dead(false) { }

    bool is_leaf();

    double get_coord(int dim);

    Point *get_point() const { return point; }

    void set_point(Point *point) { KdNode::point = point; }

    KdNode *get_left() const { return left; }

    void set_left(KdNode *left) { KdNode::left = left; }

    KdNode *get_right() const { return right; }

    void set_right(KdNode *right) { KdNode::right = right; }

    bool is_dead() const { return dead; }

    void set_dead(bool dead) { KdNode::dead = dead; }

private:
    Point *point;
    KdNode *left;
    KdNode *right;
    bool dead;
};


#endif //NNCO_KD_NODE_H
