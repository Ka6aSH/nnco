#include <gtest/gtest.h>
#include <kd_node.h>
#include <kd_tree.h>
#include <kd_algorithm.h>

bool TraverseTreeLess(KdNode *node, int axis, double median);

bool TraverseTreeGreater(KdNode *node, int axis, double median);

template<typename T>
void FreeVec(std::vector<T> *vec);

TEST(kd_structure, kd_node_leaf) {
    Point p(2, new double[1, 2]);
    KdNode leaf_node(&p);
    KdNode test_node(&p);
    EXPECT_TRUE(test_node.is_leaf());
    test_node.set_left(&leaf_node);
    EXPECT_FALSE(test_node.is_leaf());
    test_node.set_right(&leaf_node);
    EXPECT_FALSE(test_node.is_leaf());
}

TEST(kd_structure, kd_tree_selectKth) {
    std::vector<Point *> v{new Point(1, new double[1]{1}), new Point(1, new double[1]{5}),
                           new Point(1, new double[1]{1}), new Point(1, new double[1]{7}),
                           new Point(1, new double[1]{8}), new Point(1, new double[1]{3}),
                           new Point(1, new double[1]{4}), new Point(1, new double[1]{1}),
                           new Point(1, new double[1]{3}), new Point(1, new double[1]{2}),
                           new Point(1, new double[1]{0}), new Point(1, new double[1]{6})};
    KdTree::SelectKth(&v, v.size() / 2, 0);
    EXPECT_EQ(v.at(v.size() / 2)->get_coord(0), 3);

    FreeVec(&v);
}

TEST(kd_structure, kd_tree_selectKth_sorting) {
    std::vector<Point *> v{new Point(1, new double[1]{1}), new Point(1, new double[1]{9}),
                           new Point(1, new double[1]{0}), new Point(1, new double[1]{7}),
                           new Point(1, new double[1]{8}), new Point(1, new double[1]{3}),
                           new Point(1, new double[1]{4}), new Point(1, new double[1]{5}),
                           new Point(1, new double[1]{6}), new Point(1, new double[1]{2}),
                           new Point(1, new double[1]{1}), new Point(1, new double[1]{6})};
    int index = KdTree::SelectKth(&v, v.size() / 2, 0);
    double median = v.at(v.size() / 2)->get_coord(0);
    for (int i = 0; i < index; ++i)
        EXPECT_LE(v.at(i)->get_coord(0), median);
    for (int i = index; i < v.size(); ++i)
        EXPECT_GE(v.at(i)->get_coord(0), median);

    FreeVec(&v);
}

TEST(kd_structure, kd_tree_build) {
    std::vector<Point *> v{new Point(2, new double[2]{1, 1}),
                           new Point(2, new double[2]{1, -1}),
                           new Point(2, new double[2]{-1, 1}),
                           new Point(2, new double[2]{-1, -1}),
                           new Point(2, new double[2]{2, 2}),
                           new Point(2, new double[2]{2, -2}),
                           new Point(2, new double[2]{-2, 2}),
                           new Point(2, new double[2]{-2, -2})};
    KdNode *root = KdTree::BuildTree(&v, 0, 2);
    // Check one root
    double median_0 = root->get_coord(0);
    EXPECT_TRUE(TraverseTreeLess(root->get_left(), 0, median_0));
    EXPECT_TRUE(TraverseTreeGreater(root->get_right(), 0, median_0));
    // Check one level deeper
    double median_1_l = root->get_left()->get_coord(1);
    double median_1_r = root->get_right()->get_coord(1);
    EXPECT_TRUE(TraverseTreeLess(root->get_left()->get_left(), 1, median_1_l));
    EXPECT_TRUE(TraverseTreeGreater(root->get_left()->get_right(), 1, median_1_l));
    EXPECT_TRUE(TraverseTreeLess(root->get_right()->get_left(), 1, median_1_r));
    EXPECT_TRUE(TraverseTreeGreater(root->get_right()->get_right(), 1, median_1_r));

    KdTree::FreeNodes(root);
    FreeVec(&v);
}

bool TraverseTreeLess(KdNode *node, int axis, double median) {
    bool point = node->get_coord(axis) <= median;
    bool left = (node->get_left() == nullptr || TraverseTreeLess(node->get_left(), axis, median));
    bool right = (node->get_right() == nullptr || TraverseTreeLess(node->get_right(), axis, median));
    return point && left && right;
}

bool TraverseTreeGreater(KdNode *node, int axis, double median) {
    bool point = node->get_coord(axis) >= median;
    bool left = (node->get_left() == nullptr || TraverseTreeGreater(node->get_left(), axis, median));
    bool right = (node->get_right() == nullptr || TraverseTreeGreater(node->get_right(), axis, median));
    return point && left && right;
}

TEST(kd_algorithm, sanity) {
    std::vector<Point *> v{new Point(2, new double[2]{1, 1}),
                           new Point(2, new double[2]{1, -1}),
                           new Point(2, new double[2]{-1, 1}),
                           new Point(2, new double[2]{-1, -1}),
                           new Point(2, new double[2]{2, 2}),
                           new Point(2, new double[2]{2, -2}),
                           new Point(2, new double[2]{-2, 2}),
                           new Point(2, new double[2]{-2, -2})};
    KdAlgorithm alg;
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