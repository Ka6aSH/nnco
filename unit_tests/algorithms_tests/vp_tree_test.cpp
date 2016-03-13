#include <gtest/gtest.h>
#include <point.h>
#include <vp_tree.h>
#include <metrics.h>

bool traverse_tree_less(VpNode *node, Point *vantage_point, double median);

bool traverse_tree_greater(VpNode *node, Point *vantage_point, double median);

TEST(vp_structure, vp_median) {
    std::vector<Point *> v{new Point(2, new double[2]{1, 1}),
                           new Point(2, new double[2]{1, -1}),
                           new Point(2, new double[2]{-1, 1}),
                           new Point(2, new double[2]{-1, -1}),
                           new Point(2, new double[2]{2, 2}),
                           new Point(2, new double[2]{2, -2}),
                           new Point(2, new double[2]{-2, 2}),
                           new Point(2, new double[2]{-2, -2})};
    Point median(2, new double[2]{0.5, 0});
    double distance = Metrics::GetEuclideanDistance(&median, v.at(4));
    Point *p1 = v.at(4), *p2 = v.at(5);
    std::pair<int, double> result = VpTree::FindDistances(&v, &median);
    Point *result_point = v.at(result.first);

    EXPECT_TRUE(result_point == p1 || result_point == p2);
    EXPECT_DOUBLE_EQ(distance, result.second);
}

TEST(vp_structure, vp_partial_sorting) {
    std::vector<Point *> v{new Point(2, new double[2]{1, 1}),
                           new Point(2, new double[2]{1, -1}),
                           new Point(2, new double[2]{-1, 1}),
                           new Point(2, new double[2]{-1, -1}),
                           new Point(2, new double[2]{2, 2}),
                           new Point(2, new double[2]{2, -2}),
                           new Point(2, new double[2]{-2, 2}),
                           new Point(2, new double[2]{-2, -2})};
    Point median(2, new double[2]{0.5, 0});
    std::pair<int, double> result = VpTree::FindDistances(&v, &median);

    for (int i = 0; i < result.first; ++i)
        EXPECT_LE(Metrics::GetEuclideanDistance(v.at(i), &median), result.second);
    for (int i = result.first; i < v.size(); ++i)
        EXPECT_GE(Metrics::GetEuclideanDistance(v.at(i), &median), result.second);
}

TEST(vp_structure, vp_tree_build) {
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
    EXPECT_TRUE(traverse_tree_less(root->get_inside_node(), root->get_point(), median_0 + 0.5));
    EXPECT_TRUE(traverse_tree_greater(root->get_outside_node(), root->get_point(), median_0 - 0.5));
    // Check one level deepper
    double median_1_l = root->get_inside_node()->get_radius();
    double median_1_r = root->get_outside_node()->get_radius();
    EXPECT_TRUE(traverse_tree_less(root->get_inside_node()->get_inside_node(),
                                   root->get_inside_node()->get_point(),
                                   median_1_l + 0.5));
    EXPECT_TRUE(traverse_tree_greater(root->get_inside_node()->get_outside_node(),
                                      root->get_inside_node()->get_point(),
                                      median_1_l - 0.5));
    EXPECT_TRUE(traverse_tree_less(root->get_outside_node()->get_inside_node(),
                                   root->get_outside_node()->get_point(),
                                   median_1_r + 0.5));
    EXPECT_TRUE(traverse_tree_greater(root->get_outside_node()->get_outside_node(),
                                      root->get_outside_node()->get_point(),
                                      median_1_r - 0.5));
}

bool traverse_tree_less(VpNode *node, Point *vantage_point, double median) {
    bool point = Metrics::GetEuclideanDistance(node->get_point(), vantage_point) <= median;
    bool left = (node->get_inside_node() == nullptr
                 || traverse_tree_less(node->get_inside_node(), vantage_point, median));
    bool right = (node->get_outside_node() == nullptr
                  || traverse_tree_less(node->get_outside_node(), vantage_point, median));
    return point && left && right;
}

bool traverse_tree_greater(VpNode *node, Point *vantage_point, double median) {
    bool point = Metrics::GetEuclideanDistance(node->get_point(), vantage_point) >= median;
    bool left = (node->get_inside_node() == nullptr
                 || traverse_tree_greater(node->get_inside_node(), vantage_point, median));
    bool right = (node->get_outside_node() == nullptr
                  || traverse_tree_greater(node->get_outside_node(), vantage_point, median));
    return point && left && right;
}