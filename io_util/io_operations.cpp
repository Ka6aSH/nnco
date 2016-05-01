#include "io_operations.h"

std::vector<Point *> *IoOperations::ReadPoints(std::string path, int dimension) {
    std::fstream input_file(path, std::ios_base::in);
    std::vector<Point *> *result = new std::vector<Point *>();
    double temp;
    while (input_file >> temp) {
        double *coordinates = new double[dimension];
        coordinates[0] = temp;
        for (int i = 1; i < dimension; ++i) {
            input_file >> coordinates[i];
        }
        result->push_back(new Point(dimension, coordinates));
    }
    return result;
}

void IoOperations::WritePoint(std::string path, std::vector<Point *> *points, std::string delim) {
    std::ofstream outfile(path);
    for (auto iter = points->begin(); iter != points->end(); ++iter) {
        for (int i = 0; i < (*iter)->get_dim(); ++i) {
            outfile << (*iter)->get_coord(i) << delim;
        }
        outfile << std::endl;
    }
    outfile.close();
}

void IoOperations::WriteResult(std::string path, double time, double quality, std::string delim) {
    std::ofstream outfile(path);
    outfile << time << delim << quality;
    outfile.close();
}


