#ifndef NNCO_KD_ALGORITHM_H
#define NNCO_KD_ALGORITHM_H


#include "ialgorithm.h"
#include "kd_node.h"
#include "kd_tree.h"
#include "metrics.h"

class KdAlgorithm : public IAlgorithm {
public:
    KdAlgorithm() { }
    virtual ~KdAlgorithm();

    void Init(std::vector<Point *> *points);
    virtual Point *Ann(Point *);
private:
    KdNode* root = nullptr;
    int dimension = 0;

    void NnsProblem(KdNode *root, Point *p, std::pair<KdNode *, double> *best, int axis);
};


#endif //NNCO_KD_ALGORITHM_H
