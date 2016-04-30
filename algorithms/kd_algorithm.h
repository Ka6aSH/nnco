#ifndef NNCO_KD_ALGORITHM_H
#define NNCO_KD_ALGORITHM_H


#include "ialgorithm.h"
#include "kd_tree.h"

class KdAlgorithm : public IAlgorithm {
public:
    KdAlgorithm() { }

    virtual void Init(std::vector<Point *> *points, double (*distance)(Point *p1, Point *p2)) override;

    virtual Point *Ann(Point *q) override;

    virtual void InsertPoint(Point *point) override;

    virtual void RemovePoint(Point *point) override;

    virtual bool Contains(Point *point) override;

    ~KdAlgorithm();

private:
    KdNode *root = nullptr;
    int dimension = 0;

    double (*metric)(Point *p1, Point *p2);

    void NnsProblem(KdNode *root, Point *p, std::pair<KdNode *, double> *best, int axis);
};


#endif //NNCO_KD_ALGORITHM_H
