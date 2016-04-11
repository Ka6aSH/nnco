#ifndef NNCO_IALGORITHM_H
#define NNCO_IALGORITHM_H

#include <c++/vector>
#include "point.h"

class IAlgorithm {
public:
    virtual void Init(std::vector<Point *> *points) = 0;

    virtual Point *Ann(Point *q) = 0;
};

#endif //NNCO_IALGORITHM_H
