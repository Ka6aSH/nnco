#include <iostream>
#include <kd_tree.h>

using namespace std;

int main() {
//    cout << "Hello, World!" << endl;
//    return 0;
    static Point *arr[] = {new Point(1, new double[1]{1}), new Point(1, new double[1]{5}),
                           new Point(1, new double[1]{1}), new Point(1, new double[1]{7}),
                           new Point(1, new double[1]{8}), new Point(1, new double[1]{3}),
                           new Point(1, new double[1]{4}), new Point(1, new double[1]{1}),
                           new Point(1, new double[1]{3}), new Point(1, new double[1]{2}),
                           new Point(1, new double[1]{0}), new Point(1, new double[1]{6})};
    std::vector<Point*> points(arr, arr + sizeof(arr) / sizeof(arr[0]));
    std::vector<Point*> v{new Point(1, new double[1]{1}), new Point(1, new double[1]{5}),
                       new Point(1, new double[1]{1}), new Point(1, new double[1]{7}),
                       new Point(1, new double[1]{8}), new Point(1, new double[1]{3}),
                       new Point(1, new double[1]{4}), new Point(1, new double[1]{1}),
                       new Point(1, new double[1]{3}), new Point(1, new double[1]{2}),
                       new Point(1, new double[1]{0}), new Point(1, new double[1]{6})};

    KdTree::selectKth(&v, v.size()/2, 0);
    return 0;
}