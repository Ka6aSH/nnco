#ifndef NNCO_IO_OPERATIONS_H
#define NNCO_IO_OPERATIONS_H


#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <point.h>

class IoOperations {
public:
    static std::vector<Point *> *ReadPoints(std::string path, int dimension);

    static void WritePoint(std::string path, std::vector<Point *> *points, std::string delim = " ");
};


#endif //NNCO_IO_OPERATIONS_H
