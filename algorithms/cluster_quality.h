#ifndef NNCO_CLUSTER_QUALITY_H
#define NNCO_CLUSTER_QUALITY_H


#include "cluster.h"

class ClusterQuality {
public:
    static double CalculateQuality(std::vector<Cluster *> *clusters);

    static double CalculateInsideQuality(std::vector<Cluster *> *clusters);

    static double CalculateOutsideQuality(std::vector<Cluster *> *clusters);

    static double get_quality() { return quality; }

    static double get_insert_quality() { return insert_quality; }

    static double get_outside_quality() { return outside_quality; }

private:
    static double quality;
    static double insert_quality;
    static double outside_quality;

};


#endif //NNCO_CLUSTER_QUALITY_H
