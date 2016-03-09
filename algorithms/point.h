#ifndef NNCO_POINT_H
#define NNCO_POINT_H


class Point {
public:
    Point(int dimension, double *vector) : dimension(dimension), vector(vector) { }

    ~Point(void);

    double getCoord(int dim);

    int getDimension() const { return dimension; }

    double *getVector() const { return vector; }

    double dot(const Point *) const;

private:
    int dimension;
    double *vector;
};


#endif //NNCO_POINT_H
