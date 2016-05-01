#ifndef NNCO_IALGORITHM_H
#define NNCO_IALGORITHM_H

#include <vector>
#include <point.h>

class IAlgorithm {
public:
    virtual void Init(std::vector<Point *> *points, double (*distance)(Point *p1, Point *p2)) = 0;

    virtual Point *Ann(Point *q) = 0;

    virtual void InsertPoint(Point *point) = 0;

    virtual void RemovePoint(Point *point) = 0;

    virtual bool Contains(Point *point) = 0;

    virtual ~IAlgorithm() { };
};

#endif //NNCO_IALGORITHM_H
