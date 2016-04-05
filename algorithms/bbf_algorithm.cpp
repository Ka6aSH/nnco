#include "bbf_algorithm.h"

BbfNode *BbfAlgorithm::FindLeaf(Point *q) {
    BbfNode *temp = root;
    BbfNode *actual = nullptr;
    while (temp != nullptr) {
        actual = temp;
        if (q->get_coord(temp->get_sep_axis()) < temp->get_sep_coord())
            temp = temp->get_left_node();
        else
            temp = temp->get_right_node();
    }
    return actual;
}

// Lowest common ancestor
BbfNode *BbfAlgorithm::Lca(BbfNode *node1, BbfNode *node2) {
    int h1 = node1->get_deep();
    int h2 = node2->get_deep();
    BbfNode *one = node1;
    BbfNode *two = node2;
    // Align a height level
    while (h1 != h2) {
        if (h1 > h2) {
            one = one->get_parent_node();
            h1--;
        } else {
            two = two->get_parent_node();
            h2--;
        }
    }
    // go up simultaneously
    while (one != two) {
        one = one->get_parent_node();
        two = two->get_parent_node();
    }
    return one;
}

void BbfAlgorithm::PushIfBetter(std::priority_queue<Triple, std::vector<Triple>, CompareTriple> *pq,
                                BbfNode *next, BbfNode *prev, BbfNode *node_q, Point *q, double dist) {
    double distance = std::numeric_limits<double>::max();
    int m;
    BbfNode *parent;
    if (next->IsParent(prev)) {
        for (int i = 0; i < q->get_dim(); ++i) {
            distance = std::min(distance,
                                std::min(
                                        std::abs(q->get_coord(i) - prev->get_lbb(i, false)),
                                        std::abs(q->get_coord(i) - prev->get_lbb(i, true))));
        }
    } else {
        parent = Lca(next, node_q);
        m = parent->get_sep_axis();
        distance = std::min(std::abs(q->get_coord(m) - next->get_tbb(m, false)),
                            std::abs(q->get_coord(m) - next->get_tbb(m, true)));
    }
    if (distance < dist) {
        Triple t = {distance, next, prev};
        pq->push(t);
    }
}

void BbfAlgorithm::Init(std::vector<Point *> *points, int node_number) {
    if (BbfAlgorithm::root != nullptr)
        delete BbfAlgorithm::root;
    BbfAlgorithm::root = new BbfNode(points);
    BbfAlgorithm::node_count = node_number;
}

Point *BbfAlgorithm::Ann(Point *q) {
    BbfNode *node_q = FindLeaf(q);
    auto node_points = node_q->get_node_points();
    int remain_views = node_count - node_points->size();
    Point *result = node_points->at(0);
    double distance = Metrics::GetEuclideanDistance(result, q);
    double tempDistance;
    for (size_t i = 0; i < node_points->size(); ++i) {
        tempDistance = Metrics::GetEuclideanDistance(q, node_points->at(i));
        if (tempDistance < distance) {
            distance = tempDistance;
            result = node_points->at(i);
        }
    }

    if (distance == 0) {
        return result;
    }
    std::priority_queue<Triple, std::vector<Triple>, CompareTriple> pq;
    PushIfBetter(&pq, node_q->get_parent_node(), node_q, node_q, q, distance);
    while (pq.size() != 0 && remain_views > 0) {
        Triple t = pq.top();
        pq.pop();
        if (t.dist >= distance) {
            return result;
        }
        if (t.next->get_left_node() != nullptr) {
            if (t.next->get_left_node() != t.prev) {
                PushIfBetter(&pq, t.next->get_left_node(), t.next, node_q, q, distance);
            }
            if (t.next->get_right_node() != t.prev) {
                PushIfBetter(&pq, t.next->get_right_node(), t.next, node_q, q, distance);
            }
            if (t.next->get_parent_node() != nullptr && t.next->get_parent_node() != t.prev) {
                PushIfBetter(&pq, t.next->get_parent_node(), t.next, node_q, q, distance);
            }
        } else {
            node_points = t.next->get_node_points();
            remain_views -= node_points->size();
            for (size_t i = 0; i < node_points->size(); ++i) {
                tempDistance = Metrics::GetEuclideanDistance(q, node_points->at(i));
                if (tempDistance < distance) {
                    distance = tempDistance;
                    result = node_points->at(i);
                }
            }
        }
    }
    return result;
}

BbfAlgorithm::~BbfAlgorithm(void) {
    delete root;
}












