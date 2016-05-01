#include <gtest/gtest.h>
#include <point.h>
#include <io_operations.h>

class IoTest : public ::testing::Test {
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

    void FreeVec(std::vector<Point *> *vec) {
        for (size_t i = 0; i < vec->size(); ++i)
            delete vec->at(i);
    }

    std::vector<Point *> points;
};

TEST_F(IoTest, write_read) {
    std::string file_name = "IoTest.write_read";
    IoOperations::WritePoint(file_name, &points);
    auto readed_points = IoOperations::ReadPoints(file_name, points[0]->get_dim());
    for (size_t i = 0; i < readed_points->size(); ++i) {
        for (size_t j = 0; j < points[0]->get_dim(); ++j) {
            EXPECT_DOUBLE_EQ(points[i]->get_coord(j), readed_points->at(i)->get_coord(j));
        }
    }
    FreeVec(readed_points);
}
