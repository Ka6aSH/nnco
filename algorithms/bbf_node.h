#ifndef NNCO_BBF_NODE_H
#define NNCO_BBF_NODE_H


#include <vector>
#include <point.h>
#include <limits>
#include <algorithm>

/**
 * The class describe the node on BBF-tree.
 * Note that this is just a wrapper and DO NOT release any resources
 */
class BbfNode {
public:
    BbfNode(std::vector<Point *> *points, int leafPoints = 10, BbfNode *parent = nullptr, double **lbb = nullptr);

    // Checks that this node is a parent of another node crossing levels in the tree
    bool IsParent(BbfNode *node);

    // Recalculate tbb
    void InitTbb();

    // Split node if number in points
    void SplitNode();

    void InsertPoint(Point *p);

    void RemovePoint(Point *p);
    
    bool Contains(Point *point);

    int get_sep_axis() const { return m; }

    double get_sep_coord() const { return median; }

    int get_deep() const { return deep; }

    double get_lbb(int dim, bool max) { return lbb[dim][max]; }

    double get_tbb(int dim, bool max) { return tbb[dim][max]; }

    BbfNode *get_left_node() const { return left_node; }

    void set_left_node(BbfNode *left_node) { BbfNode::left_node = left_node; }

    BbfNode *get_right_node() const { return right_node; }

    void set_right_node(BbfNode *right_node) { BbfNode::right_node = right_node; }

    BbfNode *get_parent_node() const { return parent; }

    std::vector<Point *> *get_node_points() { return &node_points; }

    ~BbfNode(void);

private:
    BbfNode *left_node;
    BbfNode *right_node;
    BbfNode *parent;
    // TODO check the usage, think it is excess
    std::vector<Point *> node_points;
    // 0 min 1 max
    double **tbb;
    double **lbb;

    // Separation axis
    int m;
    // Separation coord on separation axis
    double median;
    // Deep of the node in a tree, 0 if a root
    int deep;
    // Amount of points in the leaves
    int leaf_points;
    // Dimension of points in the node
    int dim;
};


#endif //NNCO_BBF_NODE_H
