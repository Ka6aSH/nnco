#ifndef NNCO_LSH_ALGORITHM_H
#define NNCO_LSH_ALGORITHM_H


#include <c++/vector>
#include <c++/cmath>
#include "ialgorithm.h"
#include "lsh_bucket.h"

class LshAlgorithm : public IAlgorithm {
public:
    LshAlgorithm() { };

    ~LshAlgorithm();

    void Init(std::vector<Point *> *points);

    virtual Point *Ann(Point *q);

private:
    int bucketsNumber;
    LshBucket **buckets = nullptr;
};


#endif //NNCO_LSH_ALGORITHM_H
