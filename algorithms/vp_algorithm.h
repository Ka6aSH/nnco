#ifndef NNCO_VP_ALGORITHM_H
#define NNCO_VP_ALGORITHM_H


#include "ialgorithm.h"
#include "vp_tree.h"
#include "metrics.h"

class VpAlgorithm : public IAlgorithm {
public:
    VpAlgorithm() { }

    virtual void Init(std::vector<Point *> *points) override;

    virtual Point *Ann(Point *q) override;

    virtual void InsertPoint(Point *point) override;

    virtual void RemovePoint(Point *point) override;

    virtual bool Contains(Point *point) override;

    ~VpAlgorithm();

private:
    VpNode *root = nullptr;

    void NnsProblem(VpNode *root, Point *p, std::pair<VpNode *, double> *best);
};


#endif //NNCO_VP_ALGORITHM_H
