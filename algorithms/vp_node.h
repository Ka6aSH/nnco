#ifndef NNCO_VP_NODE_H
#define NNCO_VP_NODE_H


#include "point.h"

/**
 * The class describe the node on VP-tree.
 * Note that this is just a wrapper and DO NOT release any resources
 */
class VpNode {

public:
    VpNode(Point *p, double radius = 0, VpNode *inside = nullptr, VpNode *outside = nullptr)
            : p(p), inside(inside), outside(outside), radius(radius) { }
    
    Point *get_point() const { return p; }

    double get_radius() const { return radius; }

    void set_radius(double radius) { VpNode::radius = radius; }

    VpNode *get_inside_node() const { return inside; }

    void set_inside_node(VpNode *inside) { VpNode::inside = inside; }

    VpNode *get_outside_node() const { return outside; }

    void set_outside_node(VpNode *outside) { VpNode::outside = outside; }

private:
    Point *p;
    VpNode *inside;
    VpNode *outside;
    double radius;
};


#endif //NNCO_VP_NODE_H
