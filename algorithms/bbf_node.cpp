#include "bbf_node.h"

BbfNode::BbfNode(std::vector<Point *> *points, int leafPoints, BbfNode *parent, double **lbb) {
    BbfNode::nodePoints.insert(BbfNode::nodePoints.begin(), points->begin(), points->end());
    BbfNode::leafPoints = leafPoints;
    BbfNode::dim = nodePoints.at(0)->get_dim();
    BbfNode::parent = parent;
    if (parent != nullptr)
        BbfNode::deep = parent->deep + 1;
    else
        BbfNode::deep = 0;

    if (lbb == nullptr) {
        BbfNode::lbb = new double *[BbfNode::dim];
        double *temp;
        for (int i = 0; i < BbfNode::dim; ++i) {
            temp = new double[2];
            temp[0] = std::numeric_limits<double>::min();
            temp[1] = std::numeric_limits<double>::max();
            BbfNode::lbb[i] = temp;
        }
    } else {
        BbfNode::lbb = lbb;
    }

    BbfNode::tbb = new double *[BbfNode::dim];
    for (int i = 0; i < BbfNode::dim; ++i)
        BbfNode::tbb[i] = new double[2];
    BbfNode::m = 0;
    BbfNode::leftNode = nullptr;
    BbfNode::rightNode = nullptr;
    SplitNode();
}

void BbfNode::SplitNode() {
    for (int i = 0; i < BbfNode::dim; ++i) {
        BbfNode::tbb[i][0] = BbfNode::nodePoints[0]->get_coord(i);
        BbfNode::tbb[i][1] = BbfNode::nodePoints[0]->get_coord(i);
    }

    for (int i = 0; i < BbfNode::dim; ++i)
        for (int j = 0; j < BbfNode::nodePoints.size(); ++j) {
            if (BbfNode::tbb[i][0] > BbfNode::nodePoints[j]->get_coord(i))
                BbfNode::tbb[i][0] = BbfNode::nodePoints[j]->get_coord(i);
            if (BbfNode::tbb[i][1] < BbfNode::nodePoints[j]->get_coord(i))
                BbfNode::tbb[i][1] = BbfNode::nodePoints[j]->get_coord(i);
        }

    if (BbfNode::nodePoints.size() > BbfNode::leafPoints) {
        double delta = BbfNode::tbb[0][1] - BbfNode::tbb[0][0];
        for (int i = 1; i < BbfNode::dim; ++i) {
            if (delta < BbfNode::tbb[i][1] - BbfNode::tbb[i][0]) {
                delta = BbfNode::tbb[i][1] - BbfNode::tbb[i][0];
                BbfNode::m = i;
            }
        }
        std::vector<double> coords;
        for (auto i = BbfNode::nodePoints.begin(); i < BbfNode::nodePoints.end(); i++) {
            coords.push_back((*i)->get_coord(m));
        }
        std::nth_element(coords.begin(), coords.begin() + coords.size() / 2, coords.end());
        BbfNode::median = coords[coords.size() / 2];

        double **lbb_left = new double *[BbfNode::dim];
        double **lbb_right = new double *[BbfNode::dim];
        for (int i = 0; i < BbfNode::dim; ++i) {
            lbb_left[i] = BbfNode::lbb[i];
            lbb_right[i] = BbfNode::lbb[i];
        }
        lbb_left[m] = new double[2];
        lbb_right[m] = new double[2];
        for (int i = 0; i < 2; ++i) {
            lbb_left[m][i] = BbfNode::lbb[m][i];
            lbb_right[m][i] = BbfNode::lbb[m][i];
        }
        lbb_left[m][1] = BbfNode::median;
        lbb_right[m][0] = BbfNode::median;

        std::vector<Point *> points_left;
        std::vector<Point *> points_right;

        for (auto i = BbfNode::nodePoints.begin(); i < BbfNode::nodePoints.end(); i++)
            if ((*i)->get_coord(BbfNode::m) < BbfNode::median)
                points_left.push_back(*i);
            else
                points_right.push_back(*i);

        if (points_left.size() != 0 && points_right.size() != 0) {
            BbfNode::leftNode = new BbfNode(&points_left, BbfNode::leafPoints, this, lbb_left);
            BbfNode::rightNode = new BbfNode(&points_right, BbfNode::leafPoints, this, lbb_right);
        }
    }
}

bool BbfNode::IsParent(BbfNode *node) {
    BbfNode* temp = node;
    while (temp != nullptr)
    {
        if (temp->parent == this)
            return true;
        temp = temp->parent;
    }
    return false;
}

BbfNode::~BbfNode(void) {
    delete leftNode;
    delete rightNode;
    for (int i = 0; i < BbfNode::dim; ++ i) {
        delete[] tbb[i];
        delete[] lbb[i];
    }
    delete[] tbb;
    delete[] lbb;
}
