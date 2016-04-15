#ifndef NNCO_VP_ALGORITHM_H
#define NNCO_VP_ALGORITHM_H


#include "ialgorithm.h"
#include "vp_tree.h"
#include "metrics.h"

class VpAlgorithm : public IAlgorithm {
public:
    VpAlgorithm() { }

    virtual void Init(std::vector<Point *> *points);

    virtual Point *Ann(Point *);

    virtual void InsertPoint(Point *point);

    virtual void RemovePoint(Point *point);

    ~VpAlgorithm();

private:
    VpNode *root = nullptr;

    void NnsProblem(VpNode *root, Point *p, std::pair<VpNode *, double> *best);
};


#endif //NNCO_VP_ALGORITHM_H
