#ifndef NNCO_KD_ALGORITHM_H
#define NNCO_KD_ALGORITHM_H


#include "ialgorithm.h"
#include "kd_tree.h"
#include "metrics.h"

class KdAlgorithm : public IAlgorithm {
public:
    KdAlgorithm() { }

    virtual void Init(std::vector<Point *> *points);

    virtual Point *Ann(Point *) override;

    virtual void InsertPoint(Point *point) override;

    virtual void RemovePoint(Point *point) override;

    virtual bool Contains(Point *point);

    ~KdAlgorithm();

private:
    KdNode *root = nullptr;
    int dimension = 0;

    void NnsProblem(KdNode *root, Point *p, std::pair<KdNode *, double> *best, int axis);
};


#endif //NNCO_KD_ALGORITHM_H
