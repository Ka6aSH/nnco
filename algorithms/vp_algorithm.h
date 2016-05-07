#ifndef NNCO_VP_ALGORITHM_H
#define NNCO_VP_ALGORITHM_H


#include "ialgorithm.h"
#include "vp_tree.h"

class VpAlgorithm : public IAlgorithm {
public:
    VpAlgorithm() { }

    virtual void Init(std::vector<Point *> *points,
                      double (*distance)(Point *p1, Point *p2),
                      double (*dimension_distance)(double p1, double p2, int dimension) = nullptr) override;

    virtual Point *Ann(Point *q) override;

    virtual void InsertPoint(Point *point) override;

    virtual void RemovePoint(Point *point) override;

    virtual bool Contains(Point *point) override;

    ~VpAlgorithm();

private:
    VpNode *root = nullptr;

    double (*metric)(Point *p1, Point *p2);

    void NnsProblem(VpNode *root, Point *p, std::pair<VpNode *, double> *best);
};


#endif //NNCO_VP_ALGORITHM_H
