#include "bbf_node.h"

BbfNode::BbfNode(std::vector<Point *> *points, int leafPoints, BbfNode *parent, double **lbb) {
    BbfNode::node_points.insert(points->begin(), points->end());
//    BbfNode::node_points.insert(BbfNode::node_points.begin(), points->begin(), points->end());
    BbfNode::leaf_points = leafPoints;
    BbfNode::dim = (*node_points.begin())->get_dim();
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
    BbfNode::left_node = nullptr;
    BbfNode::right_node = nullptr;

    InitTbb();
    SplitNode();
}

void BbfNode::InitTbb() {
    if (node_points.empty())
        return;
    for (int i = 0; i < BbfNode::dim; ++i) {
        BbfNode::tbb[i][0] = (*node_points.begin())->get_coord(i);
        BbfNode::tbb[i][1] = (*node_points.begin())->get_coord(i);
    }

    for (int i = 0; i < BbfNode::dim; ++i)
        for (auto iter = node_points.begin(); iter != node_points.end(); ++iter) {
//        for (int j = 0; j < BbfNode::node_points.size(); ++j) {
//            if (BbfNode::tbb[i][0] > BbfNode::node_points[j]->get_coord(i))
//                BbfNode::tbb[i][0] = BbfNode::node_points[j]->get_coord(i);
//            if (BbfNode::tbb[i][1] < BbfNode::node_points[j]->get_coord(i))
//                BbfNode::tbb[i][1] = BbfNode::node_points[j]->get_coord(i);
            if (BbfNode::tbb[i][0] > (*iter)->get_coord(i))
                BbfNode::tbb[i][0] = (*iter)->get_coord(i);
            if (BbfNode::tbb[i][1] < (*iter)->get_coord(i))
                BbfNode::tbb[i][1] = (*iter)->get_coord(i);
        }
}

void BbfNode::UpdateTbb(Point *p) {
    for (int i = 0; i < BbfNode::dim; ++i) {
        if (BbfNode::tbb[i][0] > p->get_coord(i))
            BbfNode::tbb[i][0] = p->get_coord(i);
        if (BbfNode::tbb[i][1] < p->get_coord(i))
            BbfNode::tbb[i][1] = p->get_coord(i);
    }
}

//TODO
void BbfNode::UpdateRemoveTbb(Point *p) {
    if (node_points.empty())
        return;

    bool recalc = false;
    for (int i = 0; i < BbfNode::dim; ++i) {
        if (BbfNode::tbb[i][0] == p->get_coord(i) || BbfNode::tbb[i][1] == p->get_coord(i)) {
            recalc = true;
            break;
        }
    }
    if (!recalc)
        return;

    for (int i = 0; i < BbfNode::dim; ++i)
        for (auto iter = node_points.begin(); iter != node_points.end(); ++iter) {
            if (BbfNode::tbb[i][0] > (*iter)->get_coord(i))
                BbfNode::tbb[i][0] = (*iter)->get_coord(i);
            if (BbfNode::tbb[i][1] < (*iter)->get_coord(i))
                BbfNode::tbb[i][1] = (*iter)->get_coord(i);
        }
}

void BbfNode::SplitNode() {
    if (BbfNode::node_points.size() > BbfNode::leaf_points) {
        double delta = BbfNode::tbb[0][1] - BbfNode::tbb[0][0];
        for (int i = 1; i < BbfNode::dim; ++i) {
            if (delta < BbfNode::tbb[i][1] - BbfNode::tbb[i][0]) {
                delta = BbfNode::tbb[i][1] - BbfNode::tbb[i][0];
                BbfNode::m = i;
            }
        }
        std::vector<double> coords;
        for (auto i = BbfNode::node_points.begin(); i != BbfNode::node_points.end(); i++) {
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

        for (auto i = BbfNode::node_points.begin(); i != BbfNode::node_points.end(); i++)
            if ((*i)->get_coord(BbfNode::m) < BbfNode::median)
                points_left.push_back(*i);
            else
                points_right.push_back(*i);

        if (points_left.size() != 0 && points_right.size() != 0) {
            BbfNode::left_node = new BbfNode(&points_left, BbfNode::leaf_points, this, lbb_left);
            BbfNode::left_node->parent_m = m;
            BbfNode::right_node = new BbfNode(&points_right, BbfNode::leaf_points, this, lbb_right);
            BbfNode::right_node->parent_m = m;
        } else {
            delete[] lbb_left[m];
            delete[] lbb_right[m];
            delete[] lbb_left;
            delete[] lbb_right;
        }
    }
}

void BbfNode::InsertPoint(Point *p) {
    BbfNode *temp = this;
    BbfNode *actual = temp;
    while (temp != nullptr) {
        actual = temp;
        temp->get_node_points()->insert(p);
        temp->UpdateTbb(p);
        if (p->get_coord(temp->get_sep_axis()) < temp->get_sep_coord())
            temp = temp->get_left_node();
        else
            temp = temp->get_right_node();
    }
    actual->SplitNode();
}

void BbfNode::RemovePoint(Point *p) {
    BbfNode *temp = this;
    BbfNode *actual = temp;
    std::unordered_set<Point *> *temp_points = temp->get_node_points();
    while (temp != nullptr) {
        actual = temp;
        temp_points = temp->get_node_points();
        temp_points->erase(p);
//        temp->UpdateRemoveTbb(p);
        if (p->get_coord(temp->get_sep_axis()) < temp->get_sep_coord())
            temp = temp->get_left_node();
        else
            temp = temp->get_right_node();
    }
    if (temp_points->empty()) {
        if (actual->get_parent_node() != nullptr) {
            BbfNode *parent = actual->get_parent_node();
            BbfNode *left = parent->get_left_node();
            BbfNode *right = parent->get_right_node();
            parent->set_left_node(nullptr);
            parent->set_right_node(nullptr);
            parent->SplitNode();
            delete right;
            delete left;
        }
    }
}

bool BbfNode::Contains(Point *point) {
    return BbfNode::node_points.count(point);
}

bool BbfNode::IsParent(BbfNode *node) {
    BbfNode *temp = node;
    while (temp != nullptr) {
        if (temp->parent == this)
            return true;
        temp = temp->parent;
    }
    return false;
}

BbfNode::~BbfNode(void) {
    delete left_node;
    delete right_node;

    if (parent != nullptr) {
        delete[] lbb[parent_m];
    } else {
        for (int i = 0; i < BbfNode::dim; ++i) {
            delete[] lbb[i];
        }
    }

    for (int i = 0; i < BbfNode::dim; ++i) {
        delete[] tbb[i];
    }
    delete[] tbb;
    delete[] lbb;
}
