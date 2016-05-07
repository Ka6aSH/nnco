#include <iostream>
#include <ialgorithm.h>
#include <linear_algorithm.h>
#include <kd_algorithm.h>
#include <vp_algorithm.h>
#include <bbf_algorithm.h>
#include <metrics.h>
#include <lsh_algorithm.h>
#include <io_operations.h>
#include <aggl_clustering.h>
#include <cluster_quality.h>
#include "getCPUTime.c"

template<typename T>
void FreeVec(std::vector<T> *vec);

void PrintHelp();

typedef std::unordered_map<std::string, std::string> arg_list;

arg_list *ParseParam(int argc, char *argv[]) {
    auto params = new std::unordered_map<std::string, std::string>();
    if (argc % 2 == 0)
        PrintHelp();
    for (int i = 1; i < argc; i += 2) {
        params->insert({std::string(argv[i]), argv[i + 1]});
    }
    return params;
};

std::pair<double (*)(Point *, Point *), double (*)(double, double, int)>
parseMetric(arg_list *params) {
    if (!params->count("-m")) {
        return {Metrics::GetEuclideanDistance, Metrics::GetEuclideanDistance};
    }
    switch (std::stoi(params->at("-m"))) {
        case 1:
            return {Metrics::GetEuclideanDistance, Metrics::GetEuclideanDistance};
        case 2:
            return {Metrics::GetClarkDistance, Metrics::GetClarkDistance};
        case 3:
            return {Metrics::GetPenroseDistance, Metrics::GetPenroseDistance};
        case 4:
            return {Metrics::GetLorentzianDistanceSafe, Metrics::GetLorentzianDistance};
        case 5:
            return {Metrics::GetLorentzianDistanceUnsafe, Metrics::GetLorentzianDistance};
        default:
            return {Metrics::GetEuclideanDistance, Metrics::GetEuclideanDistance};
    }
}

IAlgorithm *parseAlgorithm(arg_list *params) {
    if (!params->count("-alg")) {
        return new LinearAlgorithm();
    }
    double node_number;
    int points_number;
    bool conservative;
    int buckets;
    int functions;
    switch (std::stoi(params->at("-alg"))) {
        case 1:
            return new LinearAlgorithm();
        case 2:
            return new KdAlgorithm();
        case 3:
            return new VpAlgorithm();
        case 4:
            node_number = params->count("-V") ? std::stod(params->at("-V")) : -1;
            points_number = params->count("-leaf") ? std::stoi(params->at("-leaf")) : 10;
            return new BbfAlgorithm(node_number, points_number);
        case 5:
            conservative = (bool) params->count("-brute");
            buckets = params->count("-buckets") ? std::stoi(params->at("-buckets")) : 0;
            functions = params->count("-func") ? std::stoi(params->at("-func")) : 0;
            return new LshAlgorithm(buckets, functions, conservative);
        default:
            return new LinearAlgorithm();
    }
}

int main(int argc, char *argv[]) {
    auto params = ParseParam(argc, argv);
    auto dimension = std::stoi(params->at("-d"));
    auto iterations = std::stoi(params->at("-n"));
    auto clusters_number = std::stoi(params->at("-cn"));
    auto metric = parseMetric(params);
    auto points = IoOperations::ReadPoints(params->at("-i"), dimension);
    double total_quality = 0;
    double total_time = 0;
    for (int i = 0; i < iterations; i++) {
        std::cout << "Iteration: " << i << std::endl;
        auto alg = parseAlgorithm(params);
        auto clustering = new AgglClustering(points, alg, metric, clusters_number);
        clustering->Init();
        auto startTime = getCPUTime();
        clustering->RunClustering();
        auto endTime = getCPUTime();
        auto clusters = clustering->GetClusters();
        // Check sanity
        int points_in_clusters = 0;
        for (auto iter = clusters->begin(); iter != clusters->end(); iter++) {
            points_in_clusters += (*iter)->get_points()->size();
        }
        if (clusters->size() != clusters_number) {
            std::cout << "Clusters amount did not match! Expected:" << clusters_number
            << " Actual: " << clusters->size() << std::endl;
        }
        if (points_in_clusters != points->size()) {
            std::cout << "Amount of points in clusters did not match! Expected: " << points->size()
            << " Actual: " << points_in_clusters << std::endl;
        }
        auto quality = ClusterQuality::CalculateQuality(clusters, metric.first);
        total_quality += quality;
        total_time += endTime - startTime;
        std::cout << "\t Quality: " << quality << std::endl;
        std::cout << "\t Time: " << endTime - startTime << std::endl;
        delete alg;
        delete clusters;
        delete clustering;
    }
    total_quality /= iterations;
    total_time /= iterations;

    IoOperations::WriteResult(params->at("-o"), total_time, total_quality);
    FreeVec(points);
    delete points;
    delete params;
    return 0;
}

template<typename T>
void FreeVec(std::vector<T> *vec) {
    for (size_t i = 0; i < vec->size(); ++i)
        delete vec->at(i);
}

void PrintHelp() {
    std::cout << "-i: input file" << std::endl;
    std::cout << "-o: output file" << std::endl;
    std::cout << "-d: dimension of input points" << std::endl;
    std::cout << "-n: number of iterations" << std::endl;
    std::cout << "-cn: number of clusters" << std::endl;
    std::cout << "-m: metric" << std::endl;
    std::cout << "\t 1 - Euclidean" << std::endl;
    std::cout << "\t 2 - Clark" << std::endl;
    std::cout << "\t 3 - Penrose" << std::endl;
    std::cout << "\t 4 - Lorentzian (Safe)" << std::endl;
    std::cout << "\t 5 - Lorentzian (Unsafe)" << std::endl;
    std::cout << "\t default - Euclidean" << std::endl;
    std::cout << "-alg: nearest neighbor search algorithm" << std::endl;
    std::cout << "\t 1 - Linear" << std::endl;
    std::cout << "\t 2 - KD-tree" << std::endl;
    std::cout << "\t 3 - VP-tree" << std::endl;
    std::cout << "\t 4 - Best Bin First" << std::endl;
    std::cout << "\t \t -V: a percentage of points that is allowed to view" << std::endl;
    std::cout << "\t \t -leaf: node_leaf parameter" << std::endl;
    std::cout << "\t 5 - LSH" << std::endl;
    std::cout << "\t \t -brute: if nn did not found let do brute force search (default - select random)" << std::endl;
    std::cout << "\t \t -buckets: number of buckets" << std::endl;
    std::cout << "\t \t -func: number of functions" << std::endl;
    std::cout << "\t default - Linear" << std::endl;
}
