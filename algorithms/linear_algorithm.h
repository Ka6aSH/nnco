#ifndef NNCO_LINEAR_ALGORITHM_H
#define NNCO_LINEAR_ALGORITHM_H


#include <c++/algorithm>
#include <c++/limits>
#include "ialgorithm.h"
#include "metrics.h"

class LinearAlgorithm : public IAlgorithm {
public:
    LinearAlgorithm() : points(nullptr) { }

    virtual void Init(std::vector<Point *> *points) override;

    virtual Point *Ann(Point *q) override;

    virtual void InsertPoint(Point *point);

    virtual void RemovePoint(Point *point) override;

    virtual bool Contains(Point *point) override;

    ~LinearAlgorithm();

private:
    std::vector<Point *> *points;
};


#endif //NNCO_LINEAR_ALGORITHM_H
