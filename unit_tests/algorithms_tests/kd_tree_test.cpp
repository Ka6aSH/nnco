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


TEST(kd_structure, insert_point) {
    Point p1(2, new double[2]{0, 0});
    KdNode root(&p1);

    Point p2(2, new double[2]{5, 0});
    KdTree::InsertPoint(&root, &p2);
    EXPECT_EQ(root.get_right()->get_point(), &p2);

    Point p3(2, new double[2]{-5, 0});
    KdTree::InsertPoint(&root, &p3);
    EXPECT_EQ(root.get_left()->get_point(), &p3);

    Point p4(2, new double[2]{5, 5});
    KdTree::InsertPoint(&root, &p4);
    EXPECT_EQ(root.get_right()->get_right()->get_point(), &p4);

    Point p5(2, new double[2]{-5, 5});
    KdTree::InsertPoint(&root, &p5);
    EXPECT_EQ(root.get_left()->get_right()->get_point(), &p5);
}

TEST(kd_structure, delete_point_1) {
    Point p_root(2, new double[2]{35, 60});
    Point p0(2, new double[2]{20, 45});
    Point p1(2, new double[2]{60, 80});
    Point p2(2, new double[2]{10, 35});
    Point p3(2, new double[2]{80, 40});
    Point p4(2, new double[2]{20, 20});
    Point p5(2, new double[2]{50, 30});
    Point p6(2, new double[2]{90, 60});
    Point p7(2, new double[2]{70, 20});
    Point p8(2, new double[2]{60, 10});
    // http://www.cs.umd.edu/class/spring2002/cmsc420-0401/pbasic.pdf
    KdNode kdn8(&p8);
    KdNode kdn7(&p7, &kdn8); // The article has a mistake
    KdNode kdn6(&p6);
    KdNode kdn5(&p5, &kdn7);
    KdNode kdn4(&p4);
    KdNode kdn3(&p3, &kdn5, &kdn6);
    KdNode kdn2(&p2, nullptr, &kdn4);
    KdNode kdn1(&p1, &kdn3);
    KdNode kdn0(&p0, &kdn2);
    KdNode kdn_root(&p_root, &kdn0, &kdn1);

    double median_0, median_1_l, median_1_r;
    // Check kd-tree invariance before deleting
    median_0 = kdn_root.get_coord(0);
    EXPECT_TRUE(TraverseTreeLess(kdn_root.get_left(), 0, median_0));
    EXPECT_TRUE(TraverseTreeGreater(kdn_root.get_right(), 0, median_0));
    // Check one level deeper
    median_1_l = kdn_root.get_left()->get_coord(1);
    median_1_r = kdn_root.get_right()->get_coord(1);
    EXPECT_TRUE(TraverseTreeLess(kdn_root.get_left()->get_left(), 1, median_1_l));
    EXPECT_TRUE(TraverseTreeLess(kdn_root.get_right()->get_left(), 1, median_1_r));
    // Deleting
    KdTree::RemovePoint(&kdn_root, &p_root, 0);
    // Check kd-tree invariance after deleting
    median_0 = kdn_root.get_coord(0);
    EXPECT_TRUE(TraverseTreeLess(kdn_root.get_left(), 0, median_0));
    EXPECT_TRUE(TraverseTreeGreater(kdn_root.get_right(), 0, median_0));
    median_1_l = kdn_root.get_left()->get_coord(1);
    median_1_r = kdn_root.get_right()->get_coord(1);
    EXPECT_TRUE(TraverseTreeLess(kdn_root.get_left()->get_left(), 1, median_1_l));
    EXPECT_TRUE(TraverseTreeLess(kdn_root.get_right()->get_left(), 1, median_1_r));
}

TEST(kd_structure, delete_point_2) {
    // http://www.cs.umd.edu/class/spring2002/cmsc420-0401/pbasic.pdf
    // Second tree
    Point p_root(2, new double[2]{20, 20});
    Point p0(2, new double[2]{10, 30});
    Point p1(2, new double[2]{25, 50});
    Point p2(2, new double[2]{35, 25});
    Point p3(2, new double[2]{30, 45});
    Point p4(2, new double[2]{55, 40});
    Point p5(2, new double[2]{30, 35});
    Point p6(2, new double[2]{45, 35});
    Point p7(2, new double[2]{50, 30});
    KdNode kdn7(&p7);
    KdNode kdn6(&p6, nullptr, &kdn7);
    KdNode kdn5(&p5);
    KdNode kdn4(&p4, &kdn6);
    KdNode kdn3(&p3, &kdn5);
    KdNode kdn2(&p2, &kdn3, &kdn4);
    KdNode kdn1(&p1, &kdn2);
    KdNode kdn0(&p0);
    KdNode kdn_root(&p_root, &kdn0, &kdn1);

    double median_0, median_1_r;
    // Check kd-tree invariance before deleting
    median_0 = kdn_root.get_coord(0);
    EXPECT_TRUE(TraverseTreeLess(kdn_root.get_left(), 0, median_0));
    EXPECT_TRUE(TraverseTreeGreater(kdn_root.get_right(), 0, median_0));
    // Check one level deeper
    median_1_r = kdn_root.get_right()->get_coord(1);
    EXPECT_TRUE(TraverseTreeLess(kdn_root.get_right()->get_left(), 1, median_1_r));
    // Deleting
    KdTree::RemovePoint(&kdn_root, &p_root, 0);
    // Check kd-tree invariance after deleting
    median_0 = kdn_root.get_coord(0);
    EXPECT_TRUE(TraverseTreeLess(kdn_root.get_left(), 0, median_0));
    EXPECT_TRUE(TraverseTreeGreater(kdn_root.get_right(), 0, median_0));
    median_1_r = kdn_root.get_right()->get_coord(1);
    EXPECT_TRUE(TraverseTreeGreater(kdn_root.get_right()->get_right(), 1, median_1_r));
}

TEST(kd_structure, delete_point_3) {
    std::vector<Point *> v{new Point(2, new double[2]{1, 1}),
                           new Point(2, new double[2]{1, -1}),
                           new Point(2, new double[2]{-1, 1}),
                           new Point(2, new double[2]{-1, -1}),
                           new Point(2, new double[2]{2, 2}),
                           new Point(2, new double[2]{2, -2}),
                           new Point(2, new double[2]{-2, 2}),
                           new Point(2, new double[2]{-2, -2})};
    KdNode *root = KdTree::BuildTree(&v, 0, 2);
    double median_0, median_1_l, median_1_r;
    // Check before deleting
    median_0 = root->get_coord(0);
    EXPECT_TRUE(TraverseTreeLess(root->get_left(), 0, median_0));
    EXPECT_TRUE(TraverseTreeGreater(root->get_right(), 0, median_0));
    // Check one level deeper
    median_1_l = root->get_left()->get_coord(1);
    median_1_r = root->get_right()->get_coord(1);
    EXPECT_TRUE(TraverseTreeLess(root->get_left()->get_left(), 1, median_1_l));
    EXPECT_TRUE(TraverseTreeGreater(root->get_left()->get_right(), 1, median_1_l));
    EXPECT_TRUE(TraverseTreeLess(root->get_right()->get_left(), 1, median_1_r));
    EXPECT_TRUE(TraverseTreeGreater(root->get_right()->get_right(), 1, median_1_r));
    // Delete
    KdTree::RemovePoint(root, root->get_point(), 0);
    // Check after deleting
    median_0 = root->get_coord(0);
    EXPECT_TRUE(TraverseTreeLess(root->get_left(), 0, median_0));
    EXPECT_TRUE(TraverseTreeGreater(root->get_right(), 0, median_0));
    // Check one level deeper
    median_1_l = root->get_left()->get_coord(1);
    median_1_r = root->get_right()->get_coord(1);
    EXPECT_TRUE(TraverseTreeLess(root->get_left()->get_left(), 1, median_1_l));
    EXPECT_TRUE(TraverseTreeGreater(root->get_left()->get_right(), 1, median_1_l));
    EXPECT_TRUE(TraverseTreeLess(root->get_right()->get_left(), 1, median_1_r));
    KdTree::FreeNodes(root);
    FreeVec(&v);
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
