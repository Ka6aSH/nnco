#ifndef NNCO_BBF_ALGORITHM_H
#define NNCO_BBF_ALGORITHM_H


#include <c++/vector>
#include <c++/queue>
#include "ialgorithm.h"
#include "bbf_node.h"
#include "metrics.h"

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
    BbfAlgorithm(int leaf_points = 10, int node_number = -1) : root(nullptr),
                                                               node_count(node_number),
                                                               leaf_points(leaf_points) { };

    virtual void Init(std::vector<Point *> *points);

    virtual Point *Ann(Point *q);

    ~BbfAlgorithm(void);

private:
    BbfNode *root;
    int node_count;
    int leaf_points;

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
