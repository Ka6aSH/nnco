#include <gtest/gtest.h>
#include <kd_node.h>
#include <kd_tree.h>

bool traverse_tree_less(KdNode *node, int axis, double median);
bool traverse_tree_greater(KdNode *node, int axis, double median);

TEST(kd_structure, kd_node_leaf) {
    Point p(2, new double[1, 2]);
    KdNode leaf_node(&p);
    KdNode test_node(&p);
    EXPECT_TRUE(test_node.isLeaf());
    test_node.setLeft(&leaf_node);
    EXPECT_FALSE(test_node.isLeaf());
    test_node.setRight(&leaf_node);
    EXPECT_FALSE(test_node.isLeaf());
}

TEST(kd_structure, kd_tree_selectKth) {
    std::vector<Point *> v{new Point(1, new double[1]{1}), new Point(1, new double[1]{5}),
                           new Point(1, new double[1]{1}), new Point(1, new double[1]{7}),
                           new Point(1, new double[1]{8}), new Point(1, new double[1]{3}),
                           new Point(1, new double[1]{4}), new Point(1, new double[1]{1}),
                           new Point(1, new double[1]{3}), new Point(1, new double[1]{2}),
                           new Point(1, new double[1]{0}), new Point(1, new double[1]{6})};
    KdTree::selectKth(&v, v.size() / 2, 0);
    EXPECT_EQ(v.at(v.size() / 2)->getCoord(0), 3);
}

TEST(kd_structure, kd_tree_selectKth_sorting) {
    std::vector<Point *> v{new Point(1, new double[1]{1}), new Point(1, new double[1]{9}),
                           new Point(1, new double[1]{0}), new Point(1, new double[1]{7}),
                           new Point(1, new double[1]{8}), new Point(1, new double[1]{3}),
                           new Point(1, new double[1]{4}), new Point(1, new double[1]{5}),
                           new Point(1, new double[1]{6}), new Point(1, new double[1]{2}),
                           new Point(1, new double[1]{1}), new Point(1, new double[1]{6})};
    int index = KdTree::selectKth(&v, v.size() / 2, 0);
    double median = v.at(index)->getCoord(0);
    for (int i = 0; i < index; ++i)
        EXPECT_LE(v.at(i)->getCoord(0), median);
    for (int i = index; i < v.size(); ++i)
        EXPECT_GE(v.at(i)->getCoord(0), median);
}

TEST(kd_structure, kd_tree_build) {
    std::vector<Point *> v{new Point(4, new double[2]{1, 1}),
                           new Point(4, new double[2]{1, -1}),
                           new Point(4, new double[2]{-1, 1}),
                           new Point(4, new double[2]{-1, -1}),
                           new Point(4, new double[2]{2, 2}),
                           new Point(4, new double[2]{2, -2}),
                           new Point(4, new double[2]{-2, 2}),
                           new Point(4, new double[2]{-2, -2})};
    KdNode* root = KdTree::buildTree(&v, 0, 2);
    // Check one root
    double median_0 = root->getCoord(0);
    EXPECT_TRUE(traverse_tree_less(root->getLeft(), 0, median_0));
    EXPECT_TRUE(traverse_tree_greater(root->getRight(), 0, median_0));
    // Check one level deepper
    double median_1_l = root->getLeft()->getCoord(1);
    double median_1_r = root->getRight()->getCoord(1);
    EXPECT_TRUE(traverse_tree_less(root->getLeft()->getLeft(), 1, median_1_l));
    EXPECT_TRUE(traverse_tree_greater(root->getLeft()->getRight(), 1, median_1_l));
    EXPECT_TRUE(traverse_tree_less(root->getRight()->getLeft(), 1, median_1_r));
    EXPECT_TRUE(traverse_tree_greater(root->getRight()->getRight(), 1, median_1_r));
}

bool traverse_tree_less(KdNode *node, int axis, double median) {
    bool point = node->getCoord(axis) <= median;
    bool left = (node->getLeft() == nullptr || traverse_tree_less(node->getLeft(), axis, median));
    bool right = (node->getRight() == nullptr || traverse_tree_less(node->getRight(), axis, median));
    return point && left && right;
}
bool traverse_tree_greater(KdNode *node, int axis, double median) {
    bool point = node->getCoord(axis) >= median;
    bool left = (node->getLeft() == nullptr || traverse_tree_greater(node->getLeft(), axis, median));
    bool right = (node->getRight() == nullptr || traverse_tree_greater(node->getRight(), axis, median));
    return point && left && right;
}

