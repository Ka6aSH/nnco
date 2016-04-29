#include "cluster.h"

Cluster::Cluster(std::vector<Point *> *points) {
    Cluster::points.insert(Cluster::points.begin(), points->begin(), points->end());
    Cluster::dimension = points->at(0)->get_dim();
    double *coords = new double[Cluster::dimension];
    for (int i = 0; i < dimension; i++) {
        coords[i] = 0;
    }
    center = new Point(dimension, coords);
    Cluster::CalculateCenter();
}

Cluster::Cluster(Point *point) {
    Cluster::points.push_back(point);
    Cluster::dimension = point->get_dim();
    double *coords = new double[Cluster::dimension];
    for (int i = 0; i < dimension; i++) {
        coords[i] = 0;
    }
    center = new Point(dimension, coords);
    Cluster::CalculateCenter();
}


Cluster::Cluster(Cluster *lhs, Cluster *rhs) {
    Cluster::points.insert(Cluster::points.end(),
                           lhs->points.begin(),
                           lhs->points.end());
    Cluster::points.insert(Cluster::points.end(),
                           rhs->points.begin(),
                           rhs->points.end());
    Cluster::dimension = Cluster::points[0]->get_dim();
    double *coords = new double[Cluster::dimension];
    for (int i = 0; i < dimension; i++) {
        coords[i] = 0;
    }
    center = new Point(dimension, coords);
    CalculateCenter();
}

void Cluster::CalculateCenter() {
    for (int i = 0; i < dimension; ++i) {
        double sum = 0;
        for (int j = 0; j < points.size(); ++j) {
            sum += points[j]->get_coord(i);
        }
        center->set_coord(i, sum / points.size());
    }
}

void Cluster::AddCluster(Cluster *another) {
    Cluster::points.insert(Cluster::points.end(),
                           another->points.begin(),
                           another->points.end());
    CalculateCenter();
}

void Cluster::AddPoint(Point *point) {
    Cluster::points.push_back(point);
    CalculateCenter();
}

Cluster::~Cluster() {
    delete center;
}
