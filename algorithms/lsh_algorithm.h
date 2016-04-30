#ifndef NNCO_LSH_ALGORITHM_H
#define NNCO_LSH_ALGORITHM_H


#include <vector>
#include <cmath>
#include "ialgorithm.h"
#include "lsh_bucket.h"

class LshAlgorithm : public IAlgorithm {
public:
    LshAlgorithm(int buckets = 0, int functions = 0) : buckets_number(buckets), functions_number(functions) { };

    virtual void Init(std::vector<Point *> *points, double (*distance)(Point *p1, Point *p2)) override;

    virtual Point *Ann(Point *q) override;

    virtual void InsertPoint(Point *point) override;

    virtual void RemovePoint(Point *point) override;

    virtual bool Contains(Point *point) override;

    ~LshAlgorithm();

private:
    int functions_number;
    int buckets_number;
    LshBucket **buckets = nullptr;

    double (*metric)(Point *p1, Point *p2);
};


#endif //NNCO_LSH_ALGORITHM_H
