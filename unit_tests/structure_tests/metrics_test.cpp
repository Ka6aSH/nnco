#include <gtest/gtest.h>
#include <point.h>
#include <metrics.h>

TEST(metrics, euclidian_sanity) {
    Point p1(2, new double[2]{1, 2});
    Point p2(2, new double[2]{1, 2});
    EXPECT_DOUBLE_EQ(Metrics::GetEuclideanDistance(&p1, &p2), 0);
    Point p3(2, new double[2]{2, 0});
    Point p4(2, new double[2]{0, 0});
    EXPECT_DOUBLE_EQ(Metrics::GetEuclideanDistance(&p3, &p4), 2);
}

TEST(metrics, euclidian_commutative) {
    Point p1(5, new double[5]{5, 7, 3, 2, 1});
    Point p2(5, new double[5]{6, 9, 2, 5, 1});
    EXPECT_DOUBLE_EQ(Metrics::GetEuclideanDistance(&p1, &p2),
                     Metrics::GetEuclideanDistance(&p2, &p1));
}

typedef double (*metric_t)(Point *p1, Point *p2);

class MetricConditionTest : public ::testing::Test {
private:
    void FreeVec(std::vector<Point *> *vec) {
        for (size_t i = 0; i < vec->size(); ++i)
            delete vec->at(i);
    }

protected:
    void SetUp() {
        points = {
                new Point(2, new double[2]{3, 3}),
                new Point(2, new double[2]{3, 1}),
                new Point(2, new double[2]{1, 3}),
                new Point(2, new double[2]{1, 1}),
                new Point(2, new double[2]{4, 4}),
                new Point(2, new double[2]{4, 0}),
                new Point(2, new double[2]{0, 4}),
                new Point(2, new double[2]{0, 0})
        };
    }

    void TearDown() {
        FreeVec(&points);
    }

    void TestPositive(double (*distance)(Point *p1, Point *p2)) {
        for (int i = 0; i < points.size(); ++i) {
            for (int j = 0; j < points.size(); ++j) {
                EXPECT_GE(distance(points[i], points[j]), 0);
            }
        }
    }

    void TestIdentity(double (*distance)(Point *p1, Point *p2)) {
        for (int i = 0; i < points.size(); ++i) {
            EXPECT_DOUBLE_EQ(distance(points[i], points[i]), 0);
        }
    }

    void TestSymmetry(double (*distance)(Point *p1, Point *p2)) {
        for (int i = 0; i < points.size(); ++i) {
            for (int j = 0; j < points.size(); ++j) {
                EXPECT_DOUBLE_EQ(distance(points[i], points[j]), distance(points[j], points[i]));
            }
        }
    }

    void TestTriangleInequality(double (*distance)(Point *p1, Point *p2)) {
        for (int i = 0; i < points.size(); ++i) {
            for (int j = 0; j < points.size(); ++j) {
                for (int k = 0; k < points.size(); ++k) {
                    double x_y = distance(points[i], points[j]);
                    double x_z = distance(points[i], points[k]);
                    double z_y = distance(points[k], points[j]);
                    if (x_y < x_z + z_y)
                        EXPECT_GE(x_z + z_y, x_y);
                    else
                        EXPECT_DOUBLE_EQ(x_z + z_y, x_y);
                }
            }
        }
    }

    std::vector<Point *> points;
};

TEST_F(MetricConditionTest, euclidian) {
    metric_t distance = Metrics::GetEuclideanDistance;
    TestPositive(distance);
    TestIdentity(distance);
    TestSymmetry(distance);
    TestTriangleInequality(distance);
}

TEST_F(MetricConditionTest, clark) {
    metric_t distance = Metrics::GetClarkDistance;
    TestPositive(distance);
    TestIdentity(distance);
    TestSymmetry(distance);
    TestTriangleInequality(distance);
}

TEST_F(MetricConditionTest, penrose) {
    metric_t distance = Metrics::GetPenroseDistance;
    TestPositive(distance);
    TestIdentity(distance);
    TestSymmetry(distance);
    TestTriangleInequality(distance);
}

TEST_F(MetricConditionTest, lorentzian_safe) {
    metric_t distance = Metrics::GetLorentzianDistanceSafe;
    TestPositive(distance);
    TestIdentity(distance);
    TestSymmetry(distance);
    TestTriangleInequality(distance);
}

TEST_F(MetricConditionTest, lorentzian_unsafe) {
    metric_t distance = Metrics::GetLorentzianDistanceUnsafe;
    TestPositive(distance);
    TestIdentity(distance);
    TestSymmetry(distance);
    TestTriangleInequality(distance);
}
