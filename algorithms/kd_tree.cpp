#include "kd_tree.h"

KdNode *KdTree::BuildTree(std::vector<Point *> *points, int axis, int dimension) {
    if (points->empty()) {
        return nullptr;
    } else {
        if (points->size() == 1) {
            return new KdNode(points->at(0));
        }
    }
    size_t median_index = points->size() / 2;
    std::nth_element(points->begin(), points->begin() + median_index, points->end(),
                     [&axis](Point *lhs, Point *rhs) {
                         return lhs->get_coord(axis) < rhs->get_coord(axis);
                     });
    Point *node_point = points->at(median_index);
    double median = node_point->get_coord(axis);
    int next_axis = (axis + 1) % dimension;
    std::vector<Point *> left_list;
    std::vector<Point *> right_list;
    for (size_t i = 0; i < median_index; ++i) {
        Point *selected = points->at(i);
        if (selected->get_coord(axis) < median) {
            left_list.push_back(selected);
        } else {
            right_list.push_back(selected);
        }
    }
    for (size_t i = median_index + 1; i < points->size(); ++i) {
        Point *selected = points->at(i);
        if (selected->get_coord(axis) < median) {
            left_list.push_back(selected);
        } else {
            right_list.push_back(selected);
        }
    }

    auto result_node = new KdNode(node_point,
                                  BuildTree(&left_list, next_axis, dimension),
                                  BuildTree(&right_list, next_axis, dimension));
    return result_node;
}

void KdTree::InsertPoint(KdNode *root, Point *point) {
    int axis = 0;
    int dimension = root->get_point()->get_dim();
    KdNode *temp = root;
    KdNode *last = root;

    while (temp != nullptr) {
        last = temp;
        int current_axis = axis % dimension;
        if (temp->get_coord(current_axis) > point->get_coord(current_axis)) {
            temp = temp->get_left();
        } else {
            temp = temp->get_right();
        }
        axis++;
    }

    int current_axis = (axis - 1) % dimension;
    if (last->get_coord(current_axis) > point->get_coord(current_axis)) {
        last->set_left(new KdNode(point));
    } else {
        last->set_right(new KdNode(point));
    }
}

//Point *KdTree::MinFunction(Point *p1, Point *p2, Point *p3, int dim) {
//    double a, b, c;
//    if (p1 == nullptr)
//        a = std::numeric_limits<double>::max();
//    else
//        a = p1->get_coord(dim);
//    if (p2 == nullptr)
//        b = std::numeric_limits<double>::max();
//    else
//        b = p2->get_coord(dim);
//
//    if (p3 == nullptr)
//        c = std::numeric_limits<double>::max();
//    else
//        c = p3->get_coord(dim);
//
//    if (a < b && a < c)
//        return p1;
//    else if (a < b && c <= a || b <= a && c <= b)
//        return p3;
//    else if (b <= a && b < c)
//        return p2;
//    return nullptr;
//}

//Point *KdTree::MaxFunction(Point *p1, Point *p2, Point *p3, int dim) {
//    double a, b, c;
//    if (p1 == nullptr)
//        a = std::numeric_limits<double>::max();
//    else
//        a = p1->get_coord(dim);
//    if (p2 == nullptr)
//        b = std::numeric_limits<double>::max();
//    else
//        b = p2->get_coord(dim);
//
//    if (p3 == nullptr)
//        c = std::numeric_limits<double>::max();
//    else
//        c = p3->get_coord(dim);
//
//    if (a > b && a > c)
//        return p1;
//    else if (a > b && c >= a || b >= a && c >= b)
//        return p3;
//    else if (b >= a && b > c)
//        return p2;
//    return nullptr;
//}

//Point *KdTree::FindMin(KdNode *node, int cutting_axis, int current_axis) {
//    if (node == nullptr) {
//        return nullptr;
//    } else if (current_axis == cutting_axis) {
//        if (node->get_left() == nullptr) {
//            return node->get_point();
//        } else {
//            return FindMin(node->get_left(), cutting_axis, (current_axis + 1) % node->get_point()->get_dim());
//        }
//    } else {
//        int next_dim = (current_axis + 1) % node->get_point()->get_dim();
//        Point *left = FindMin(node->get_left(), cutting_axis, next_dim);
//        Point *right = FindMin(node->get_right(), cutting_axis, next_dim);
//
//        double a, b, c;
//        if (left == nullptr)
//            a = std::numeric_limits<double>::max();
//        else
//            a = left->get_coord(cutting_axis);
//
//        if (right == nullptr)
//            b = std::numeric_limits<double>::max();
//        else
//            b = right->get_coord(cutting_axis);
//
//        c = node->get_coord(cutting_axis);
//
//        if (a < b && a < c)
//            return left;
//        else if (a < b && c <= a || b <= a && c <= b)
//            return node->get_point();
//        else if (b <= a && b < c)
//            return right;
//        return nullptr;
//    }
//}

//KdNode *KdTree::RemovePoint(KdNode *root, Point *point, int axis) {
//    if (root == nullptr) {
//        return nullptr;
//    }
//    int next_axis = (axis + 1) % root->get_point()->get_dim();
//
//    if (point == root->get_point()) {
//        if (root->get_right() != nullptr) {
//            root->set_point(FindMin(root->get_right(), axis, next_axis));
//            root->set_right(RemovePoint(root->get_right(), root->get_point(), next_axis));
//        } else if (root->get_left() != nullptr) {
//            root->set_point(FindMin(root->get_left(), axis, next_axis));
//            root->set_right(RemovePoint(root->get_left(), root->get_point(), next_axis));
//            root->set_left(nullptr);
//        } else {
//            delete root;
//            return nullptr;
//        }
//    } else if (point->get_coord(axis) < root->get_coord(axis)) {
//        root->set_left(RemovePoint(root->get_left(), point, next_axis));
//    } else {
//        root->set_right(RemovePoint(root->get_right(), point, next_axis));
//    }
//    return root;
//}

void KdTree::RemovePoint(KdNode *root, Point *point) {
    int axis = 0;
    int dimension = root->get_point()->get_dim();
    KdNode *temp = root;

    while (temp->get_point() != point) {
        int current_axis = axis % dimension;
        if (temp->get_coord(current_axis) > point->get_coord(current_axis)) {
            temp = temp->get_left();
        } else {
            temp = temp->get_right();
        }
        axis++;
    }

    temp->set_dead(true);
}

bool KdTree::Contains(KdNode *root, Point *point) {
    int axis = 0;
    int dimension = root->get_point()->get_dim();
    KdNode *temp = root;

    while (temp != nullptr) {
        if (!temp->is_dead() && temp->get_point() == point) {
            return true;
        }
        int current_axis = axis % dimension;
        if (temp->get_coord(current_axis) > point->get_coord(current_axis)) {
            temp = temp->get_left();
        } else {
            temp = temp->get_right();
        }
        axis++;
    }
    return false;
}

void KdTree::FreeNodes(KdNode *root) {
    if (root == nullptr)
        return;

    KdTree::FreeNodes(root->get_left());
    KdTree::FreeNodes(root->get_right());

    delete root;
}
