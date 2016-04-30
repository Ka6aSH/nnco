#ifndef NNCO_LINEAR_ALGORITHM_H
#define NNCO_LINEAR_ALGORITHM_H


#include <algorithm>
#include <limits>
#include "ialgorithm.h"

class LinearAlgorithm : public IAlgorithm {
public:
    LinearAlgorithm() : points(nullptr) { }

    virtual void Init(std::vector<Point *> *points, double (*distance)(Point *p1, Point *p2)) override;

    virtual Point *Ann(Point *q) override;

    virtual void InsertPoint(Point *point);

    virtual void RemovePoint(Point *point) override;

    virtual bool Contains(Point *point) override;

    virtual ~LinearAlgorithm();

private:
    std::vector<Point *> *points;

    double (*metric)(Point *p1, Point *p2);
};


#endif //NNCO_LINEAR_ALGORITHM_H
