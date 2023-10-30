#include "RotatedRect.h"
#include <cmath>

constexpr double PI_RR = 3.14159265358979323846;

using namespace rf;

// RotatedRect(const Point2d<double> &point1, const Point2d<double> &point2, const Point2d<double> &point3);


// void Set(const Point2d<double> &point1, const Point2d<double> &point2, const Point2d<double> &point3);

RotatedRect::RotatedRect() : center(0.0, 0.0), width(1.0), height(1.0), angle(0)
{
}

RotatedRect::RotatedRect(const Point2d<double> &center_, double width_, double height_, double angle_) : center(center_), width(width_), height(height_), angle(angle_){};

RotatedRect::RotatedRect(const Point2d<double> &point1, const Point2d<double> &point2, const Point2d<double> &point3)
{
	Set(point1, point2, point3);
}

void RotatedRect::Set(const Point2d<double> &point1, const Point2d<double> &point2, const Point2d<double> &point3)
{
    center = (point1 + point3) * 0.5f;
    width = norm(point1 - point2);
    height = norm(point1 - point3);
    angle = std::atan2(point2.y - point1.y, point2.x - point1.x) * 180.0 / PI_RR;
}

void RotatedRect::Set(const Point2d<double> &center_, double width_, double height_, double angle_)
{
	center = center_;
	width = width_;
	height = height_;
	angle = angle_;
}

//TODO Not implemented
 Rect RotatedRect::BoundingRect()
 {
	auto rectPoints = RectPoints();
	// Нахождение минимальных и максимальных координат
    double minX {std::numeric_limits<double>::max()};
    double minY {std::numeric_limits<double>::max()};
    double maxX {std::numeric_limits<double>::min()};
    double maxY {std::numeric_limits<double>::min()};

    for (const auto& point : rectPoints) {
        if (point.x < minX) {
            minX = point.x;
        }
        if (point.y < minY) {
            minY = point.y;
        }
        if (point.x > maxX) {
            maxX = point.x;
        }
        if (point.y > maxY) {
            maxY = point.y;
        }
    }
	return Rect();
 }


 std::vector<Point2d<double>> RotatedRect::RectPoints()
{
    double radAngle = angle * PI_RR / 180.0;
    double halfWidth = width / 2.0;
    double halfHeight = height / 2.0;
    double cosAngle = std::cos(radAngle);
    double sinAngle = std::sin(radAngle);

    // Вычисление вершин прямоугольника
    std::vector<Point2d<double>> rectPoints(4);
    rectPoints[0] = Point2d<double>(center.x - halfWidth * cosAngle - halfHeight * sinAngle,
                               center.y + halfWidth * sinAngle - halfHeight * cosAngle);
    rectPoints[1] = Point2d<double>(center.x + halfWidth * cosAngle - halfHeight * sinAngle,
                               center.y - halfWidth * sinAngle - halfHeight * cosAngle);
    rectPoints[2] = Point2d<double>(center.x + halfWidth * cosAngle + halfHeight * sinAngle,
                               center.y - halfWidth * sinAngle + halfHeight * cosAngle);
    rectPoints[3] = Point2d<double>(center.x - halfWidth * cosAngle + halfHeight * sinAngle,
                               center.y + halfWidth * sinAngle + halfHeight * cosAngle);

    return rectPoints;
}

