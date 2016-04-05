#ifndef NNCO_BBF_NODE_H
#define NNCO_BBF_NODE_H


#include <c++/vector>
#include "point.h"
#include <c++/limits>
#include <c++/algorithm>

/**
 * The class describe the node on BBF-tree.
 * Note that this is just a wrapper and DO NOT release any resources
 */
class BbfNode {
public:
    BbfNode(std::vector<Point*>* points, int leafPoints = 10, BbfNode* parent = nullptr, double** lbb = nullptr);

    // Checks that this node is a parent of another node crossing levels in the tree
    bool IsParent(BbfNode *node);


    int get_sep_axis() const { return m; }

    double get_sep_coord() const { return median; }

    int get_deep() const { return deep; }

    double get_lbb(int dim, bool max) { return lbb[dim][max]; }

    double get_tbb(int dim, bool max) { return tbb[dim][max]; }

    BbfNode *get_left_node() const { return leftNode; }

    BbfNode *get_right_node() const { return rightNode; }

    BbfNode *get_parent_node() const { return parent; }

    const std::vector<Point *> *get_node_points() const { return &nodePoints; }

    ~BbfNode(void);

private:
    void SplitNode();

    BbfNode* leftNode;
    BbfNode* rightNode;
    BbfNode* parent;
    // TODO check the usage, think it is excess
    std::vector<Point*> nodePoints;
    // 0 min 1 max
    double** tbb;
    double** lbb;

    // Separation axis
    int m;
    // Separation coord on separation axis
    double median;
    // Deep of the node in a tree, 0 if a root
    int deep;
    // Amount of points in the leaves
    int leafPoints;
    // Dimension of points in the node
    int dim;
};


#endif //NNCO_BBF_NODE_H
