#include <gtest/gtest.h>
#include <point.h>
#include <vp_tree.h>
#include <vp_algorithm.h>

bool TraverseTreeLess(VpNode *node, Point *vantage_point, double median);

bool TraverseTreeGreater(VpNode *node, Point *vantage_point, double median);

template<typename T>
void FreeVec(std::vector<T> *vec);

TEST(vp_structure, vp_tree_build) {
    srand(time(NULL));
    std::vector<Point *> v{new Point(2, new double[2]{1, 1}),
                           new Point(2, new double[2]{1, -1}),
                           new Point(2, new double[2]{-1, 1}),
                           new Point(2, new double[2]{-1, -1}),
                           new Point(2, new double[2]{2, 2}),
                           new Point(2, new double[2]{2, -2}),
                           new Point(2, new double[2]{-2, 2}),
                           new Point(2, new double[2]{-2, -2})};
    VpNode *root = VpTree::BuildTree(&v);
    // Check one root
    double median_0 = root->get_radius();
    EXPECT_TRUE(TraverseTreeLess(root->get_inside_node(), root->get_point(), median_0 + 0.01));
    EXPECT_TRUE(TraverseTreeGreater(root->get_outside_node(), root->get_point(), median_0 - 0.01));

    VpTree::FreeNodes(root);
    FreeVec(&v);
}

bool TraverseTreeLess(VpNode *node, Point *vantage_point, double median) {
    bool point = Metrics::GetEuclideanDistance(node->get_point(), vantage_point) <= median;
    bool left = (node->get_inside_node() == nullptr
                 || TraverseTreeLess(node->get_inside_node(), vantage_point, median));
    bool right = (node->get_outside_node() == nullptr
                  || TraverseTreeLess(node->get_outside_node(), vantage_point, median));
    return point && left && right;
}

bool TraverseTreeGreater(VpNode *node, Point *vantage_point, double median) {
    bool point = Metrics::GetEuclideanDistance(node->get_point(), vantage_point) >= median;
    bool left = (node->get_inside_node() == nullptr
                 || TraverseTreeGreater(node->get_inside_node(), vantage_point, median));
    bool right = (node->get_outside_node() == nullptr
                  || TraverseTreeGreater(node->get_outside_node(), vantage_point, median));
    return point && left && right;
}

TEST(vp_structure, delete_point) {
    srand(time(NULL));
    std::vector<Point *> v{new Point(2, new double[2]{1, 1}),
                           new Point(2, new double[2]{1, -1}),
                           new Point(2, new double[2]{-1, 1}),
                           new Point(2, new double[2]{-1, -1}),
                           new Point(2, new double[2]{2, 2}),
                           new Point(2, new double[2]{2, -2}),
                           new Point(2, new double[2]{-2, 2}),
                           new Point(2, new double[2]{-2, -2})};
    VpAlgorithm alg;
    alg.Init(&v);

    alg.RemovePoint(v.at(0));
    Point p1(2, new double[2]{0.5, 0.5});
    EXPECT_NE(v.at(0), alg.Ann(&p1));

    alg.RemovePoint(v.at(7));
    Point p2(2, new double[2]{-5, -5});
    EXPECT_NE(v.at(7), alg.Ann(&p2));

    alg.RemovePoint(v.at(2));
    Point p3(2, new double[2]{-2, 0.5});
    EXPECT_NE(v.at(2), alg.Ann(&p3));

    alg.RemovePoint(v.at(1));
    Point p4(2, new double[2]{1, -0.0001});
    EXPECT_NE(v.at(1), alg.Ann(&p4));

    FreeVec(&v);
}

TEST(vp_structure, insert_point) {
    srand(time(NULL));
    std::vector<Point *> v{new Point(2, new double[2]{1, 1}),
                           new Point(2, new double[2]{1, -1}),
                           new Point(2, new double[2]{-1, 1}),
                           new Point(2, new double[2]{-1, -1})};
    VpAlgorithm alg;
    alg.Init(&v);

    Point ip1(2, new double[2]{2, 2});
    Point ip2(2, new double[2]{2, -2});
    Point ip3(2, new double[2]{-2, 2});
    Point ip4(2, new double[2]{-2, -2});

    alg.InsertPoint(&ip1);
    alg.InsertPoint(&ip2);
    alg.InsertPoint(&ip3);
    alg.InsertPoint(&ip4);

    Point p1(2, new double[2]{3, 3});
    EXPECT_EQ(&ip1, alg.Ann(&p1));

    Point p2(2, new double[2]{3, -3});
    EXPECT_EQ(&ip2, alg.Ann(&p2));

    Point p3(2, new double[2]{-3, 3});
    EXPECT_EQ(&ip3, alg.Ann(&p3));

    Point p4(2, new double[2]{-3, -3});
    EXPECT_EQ(&ip4, alg.Ann(&p4));

    FreeVec(&v);
}

TEST(vp_algorithm, sanity) {
    srand(time(NULL));
    std::vector<Point *> v{new Point(2, new double[2]{1, 1}),
                           new Point(2, new double[2]{1, -1}),
                           new Point(2, new double[2]{-1, 1}),
                           new Point(2, new double[2]{-1, -1}),
                           new Point(2, new double[2]{2, 2}),
                           new Point(2, new double[2]{2, -2}),
                           new Point(2, new double[2]{-2, 2}),
                           new Point(2, new double[2]{-2, -2})};
    VpAlgorithm alg;
    alg.Init(&v);
    Point p1(2, new double[2]{0.5, 0.5});
    EXPECT_EQ(v.at(0), alg.Ann(&p1));
    Point p2(2, new double[2]{-5, -5});
    EXPECT_EQ(v.at(7), alg.Ann(&p2));
    Point p3(2, new double[2]{-2, 0.5});
    EXPECT_EQ(v.at(2), alg.Ann(&p3));
    Point p4(2, new double[2]{1, -0.0001});
    EXPECT_EQ(v.at(1), alg.Ann(&p4));

    FreeVec(&v);
}

template<typename T>
void FreeVec(std::vector<T> *vec) {
    for (size_t i = 0; i < vec->size(); ++i)
        delete vec->at(i);
}
