#ifndef NNCO_VP_ALGORITHM_H
#define NNCO_VP_ALGORITHM_H


#include "ialgorithm.h"
#include "vp_node.h"
#include "vp_tree.h"
#include "metrics.h"

class VpAlgorithm : public IAlgorithm {
public:
    VpAlgorithm() { }

    virtual ~VpAlgorithm();

    void Init(std::vector<Point *> *points);

    virtual Point *Ann(Point *);

private:
    VpNode *root = nullptr;

    void NnsProblem(VpNode *root, Point *p, std::pair<VpNode *, double> *best);
};


#endif //NNCO_VP_ALGORITHM_H