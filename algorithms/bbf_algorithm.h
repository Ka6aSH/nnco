#ifndef NNCO_BBF_ALGORITHM_H
#define NNCO_BBF_ALGORITHM_H


#include <vector>
#include <queue>
#include "ialgorithm.h"
#include "bbf_node.h"

struct Triple {
    double dist;
    BbfNode *next;
    BbfNode *prev;
};

class CompareTriple {
public:
    bool operator()(Triple &t1, Triple &t2) {
        return t1.dist < t2.dist;
    }
};

class BbfAlgorithm : public IAlgorithm {
public:
    BbfAlgorithm(int node_number = -1, int leaf_points = 10) : root(nullptr),
                                                               node_count(node_number),
                                                               node_part(-1),
                                                               leaf_points(leaf_points) { };

    BbfAlgorithm(double node_part = -1, int leaf_points = 10) : root(nullptr),
                                                                node_count(-1),
                                                                node_part(node_part),
                                                                leaf_points(leaf_points) { };

    virtual void Init(std::vector<Point *> *points, double (*distance)(Point *p1, Point *p2)) override;

    virtual Point *Ann(Point *q) override;

    virtual void InsertPoint(Point *point) override;

    virtual void RemovePoint(Point *point) override;

    virtual bool Contains(Point *point) override;

    ~BbfAlgorithm(void);

private:
    BbfNode *root;
    double node_part;
    int node_count;
    int leaf_points;

    double (*metric)(Point *p1, Point *p2);

    BbfNode *FindLeaf(Point *q);

    BbfNode *Lca(BbfNode *node1, BbfNode *node2);

    void PushIfBetter(std::priority_queue<Triple, std::vector<Triple>, CompareTriple> *pq,
                      BbfNode *next,
                      BbfNode *prev,
                      BbfNode *node_q,
                      Point *q,
                      double dist);
};


#endif //NNCO_BBF_ALGORITHM_H
