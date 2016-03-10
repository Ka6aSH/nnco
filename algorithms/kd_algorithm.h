#ifndef NNCO_KD_ALGORITHM_H
#define NNCO_KD_ALGORITHM_H

#include <algorithm>
#include <c++/bits/stl_vector.h>
#include <c++/bits/stl_pair.h>
#include "ialgorithm.h"
#include "kd_node.h"
#include "kd_tree.h"
#include "metrics.h"

class KdAlgorithm : public IAlgorithm {
public:
    KdAlgorithm() { }
    virtual ~KdAlgorithm();

    void init(std::vector<Point*>* points);
    virtual Point *Ann(Point*);
private:
    KdNode* root;
    int dimension;

    void nnsProblem(KdNode* root, Point* p, std::pair<KdNode*, double>* best, int axis);
};


#endif //NNCO_KD_ALGORITHM_H
