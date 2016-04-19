#ifndef NNCO_LSH_ALGORITHM_H
#define NNCO_LSH_ALGORITHM_H


#include <c++/vector>
#include <c++/cmath>
#include "ialgorithm.h"
#include "lsh_bucket.h"

class LshAlgorithm : public IAlgorithm {
public:
    LshAlgorithm(int buckets = 0, int functions = 0) : buckets_number(buckets), functions_number(functions) { };

    virtual void Init(std::vector<Point *> *points) override;

    virtual Point *Ann(Point *q) override;

    virtual void InsertPoint(Point *point) override;

    virtual void RemovePoint(Point *point) override;

    virtual bool Contains(Point *point);

    ~LshAlgorithm();

private:
    int functions_number;
    int buckets_number;
    LshBucket **buckets = nullptr;
};


#endif //NNCO_LSH_ALGORITHM_H
