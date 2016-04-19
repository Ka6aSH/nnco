#include <gtest/gtest.h>
#include <point.h>
#include <bbf_node.h>
#include <bbf_algorithm.h>

class BbfTreeTest : public ::testing::Test {
private:
    void FreeVec(std::vector<Point *> *vec) {
        for (size_t i = 0; i < vec->size(); ++i)
            delete vec->at(i);
    }

protected:
    void SetUp() {
        v = new std::vector<Point *>
                {new Point(2, new double[2]{-6, 2}),
                 new Point(2, new double[2]{-6, -2}),
                 new Point(2, new double[2]{-5, 2}),
                 new Point(2, new double[2]{-5, -2}),
                 new Point(2, new double[2]{-4, 2}),
                 new Point(2, new double[2]{-4, -2}),
                 new Point(2, new double[2]{4, 1}),
                 new Point(2, new double[2]{4, 0}),
                 new Point(2, new double[2]{4, -1}),
                 new Point(2, new double[2]{8, 1}),
                 new Point(2, new double[2]{8, 0}),
                 new Point(2, new double[2]{8, -1})};
        rootNode = new BbfNode(v, kLeafPoints);
    }

    void TearDown() {
        delete rootNode;
        FreeVec(v);
        delete v;
    }

    const int kLeafPoints = 3;
    BbfNode *rootNode;
    std::vector<Point *> *v;
};

TEST_F(BbfTreeTest, deviation) {
    EXPECT_EQ(rootNode->get_sep_axis(), 0);
    EXPECT_EQ(rootNode->get_left_node()->get_sep_axis(), 1);
    EXPECT_EQ(rootNode->get_right_node()->get_sep_axis(), 0);
}

TEST_F(BbfTreeTest, leafPoints) {
    // Check this one
    //    /   \
    //   / \ / \
    //   *
    EXPECT_TRUE(rootNode->get_left_node()->get_left_node()->get_left_node() == nullptr
                && rootNode->get_left_node()->get_left_node()->get_right_node() == nullptr);
    EXPECT_LE(rootNode->get_left_node()->get_left_node()->get_node_points()->size(), kLeafPoints);
    // Check this one
    //    /   \
    //   / \ / \
    //     *
    EXPECT_TRUE(rootNode->get_left_node()->get_right_node()->get_left_node() == nullptr
                && rootNode->get_left_node()->get_right_node()->get_right_node() == nullptr);
    EXPECT_LE(rootNode->get_left_node()->get_right_node()->get_node_points()->size(), kLeafPoints);
    // Check this one
    //    /   \
    //   / \ / \
    //       *
    EXPECT_TRUE(rootNode->get_right_node()->get_left_node()->get_left_node() == nullptr
                && rootNode->get_right_node()->get_left_node()->get_right_node() == nullptr);
    EXPECT_LE(rootNode->get_right_node()->get_left_node()->get_node_points()->size(), kLeafPoints);
    // Check this one
    //    /   \
    //   / \ / \
    //         *
    EXPECT_TRUE(rootNode->get_right_node()->get_right_node()->get_left_node() == nullptr
                && rootNode->get_right_node()->get_right_node()->get_right_node() == nullptr);
    EXPECT_LE(rootNode->get_right_node()->get_right_node()->get_node_points()->size(), kLeafPoints);
}

TEST_F(BbfTreeTest, balancing) {
    EXPECT_EQ(rootNode->get_left_node()->get_node_points()->size(),
              rootNode->get_right_node()->get_node_points()->size());
    EXPECT_EQ(rootNode->get_left_node()->get_left_node()->get_node_points()->size(),
              rootNode->get_left_node()->get_right_node()->get_node_points()->size());
    EXPECT_EQ(rootNode->get_right_node()->get_left_node()->get_node_points()->size(),
              rootNode->get_right_node()->get_right_node()->get_node_points()->size());
}

TEST_F(BbfTreeTest, deep) {
    EXPECT_EQ(rootNode->get_deep(), 0);
    EXPECT_EQ(rootNode->get_left_node()->get_deep(), 1);
    EXPECT_EQ(rootNode->get_right_node()->get_deep(), 1);
    EXPECT_EQ(rootNode->get_left_node()->get_left_node()->get_deep(), 2);
    EXPECT_EQ(rootNode->get_left_node()->get_right_node()->get_deep(), 2);
    EXPECT_EQ(rootNode->get_right_node()->get_left_node()->get_deep(), 2);
    EXPECT_EQ(rootNode->get_right_node()->get_right_node()->get_deep(), 2);
}

TEST_F(BbfTreeTest, paranting) {
    // Simple check
    EXPECT_TRUE(rootNode->IsParent(rootNode->get_left_node()));
    EXPECT_TRUE(rootNode->IsParent(rootNode->get_right_node()));
    // Check through the level
    EXPECT_TRUE(rootNode->IsParent(rootNode->get_left_node()->get_left_node()));
    EXPECT_TRUE(rootNode->IsParent(rootNode->get_left_node()->get_right_node()));
    EXPECT_TRUE(rootNode->IsParent(rootNode->get_right_node()->get_left_node()));
    EXPECT_TRUE(rootNode->IsParent(rootNode->get_right_node()->get_right_node()));
    // Check neighbor subtrees
    EXPECT_FALSE(rootNode->get_left_node()->IsParent(rootNode->get_right_node()));
    // Check neighbor subtree through the level
    EXPECT_FALSE(rootNode->get_left_node()->IsParent(rootNode->get_right_node()->get_left_node()));
}

TEST_F(BbfTreeTest, search) {
    BbfAlgorithm alg;
    alg.Init(v);
    Point p1(2, new double[2]{0, 0});
    EXPECT_EQ(v->at(7), alg.Ann(&p1));
    Point p2(2, new double[2]{-1, -1});
    EXPECT_EQ(v->at(5), alg.Ann(&p2));
    Point p3(2, new double[2]{4, 1});
    EXPECT_EQ(v->at(6), alg.Ann(&p3));
}

TEST_F(BbfTreeTest, insert) {
    BbfAlgorithm alg(3);
    std::vector<Point *> sub_vec(v->begin(), v->begin() + v->size() / 2);
    alg.Init(&sub_vec);
    for (auto iter = v->begin() + v->size() / 2; iter != v->end(); iter++) {
        alg.InsertPoint(*iter);
    }
    Point p1(2, new double[2]{8, -2});
    EXPECT_EQ(v->at(11), alg.Ann(&p1));
}


TEST_F(BbfTreeTest, remove) {
    BbfAlgorithm alg(3);
    std::vector<Point *> sub_vec(v->begin(), v->begin() + v->size() / 2);
    alg.Init(&sub_vec);
    for (auto iter = v->begin() + v->size() / 2; iter != v->end(); iter++) {
        alg.InsertPoint(*iter);
    }
    alg.RemovePoint(v->at(5));
    Point p1(2, new double[2]{8, -2});
    EXPECT_EQ(v->at(11), alg.Ann(&p1));
}

TEST_F(BbfTreeTest, contains) {
    for (int i = 0; i < v->size(); ++i) {
        EXPECT_TRUE(rootNode->Contains(v->at(i)));
    }
}