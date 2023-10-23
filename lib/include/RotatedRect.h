#pragma once
#include <vector>

#include "Point2d.h"
#include "Rect.h"
namespace rf
{

	class RotatedRect
	{
	public:
		RotatedRect();
		RotatedRect(const Point2d<double> &center, double width, double height, double angle);
		RotatedRect(const Point2d<double> &point1, const Point2d<double> &point2, const Point2d<double> &point3);

		~RotatedRect() {}

		void Set(const Point2d<double> &center, double width, double height, double angle);
		void Set(const Point2d<double> &point1, const Point2d<double> &point2, const Point2d<double> &point3);
		void SetWidth(double width_) { width = width_; }
		void SetHeight(double height_) { height = height_; }
        void SetCenter(const Point2d<double> &center_) { center = center_; }

		Point2d<double> Center() const { return center; };
		double Width() const { return width; }
		double Height() const { return height; }
		//in radian
        double Angle() const { return angle; }
        std::vector<Point2d<double>> RectPoints();
        Rect BoundingRect ();
	private:
		Point2d<double> center; // center
		double width;			 // right bottom point
		double height;
		double angle;  // angle in Degree
	};

}
