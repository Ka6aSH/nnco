#ifndef NNCO_IALGORITHM_H
#define NNCO_IALGORITHM_H


#include "point.h"

class IAlgorithm
{
public:
    virtual Point* ANN(Point*) = 0;
    //virtual std::vector<MyPoint*>* ENN(MyPoint*) = 0;
};

#endif //NNCO_IALGORITHM_H
