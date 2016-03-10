#ifndef NNCO_POINT_H
#define NNCO_POINT_H


class Point {
public:
    Point(int dimension, double *vector) : dimension(dimension), vector(vector) { }

    ~Point(void);

    double get_coord(int dim);

    int get_dim() const { return dimension; }

    double *get_vec() const { return vector; }

    double Dot(const Point *) const;

private:
    int dimension;
    double *vector;
};


#endif //NNCO_POINT_H
