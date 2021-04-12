#pragma once

#include "Point2d.h"

namespace rf
{

	class Rect
	{
	public:
		Rect();
		Rect(const Point2d<double> &pointTl, double width, double height);
		Rect(const Point2d<double> &point1, const Point2d<double> &point2);

		~Rect() {}

		void Set(const Point2d<double> &point1, const Point2d<double> &point2);
		void Set(const Point2d<double> &point1, double width, double height);
		void SetWidth(double width_) { width_ = width_; }
		void SetHeight(double height_) { height = height_; }

		Point2d<double> PointTl() const { return pointTl; };
		double Width() const { return width; }
		double Height() const { return height; }

	private:
		Point2d<double> pointTl; // left-top point
		double width;			 // right bottom point
		double height;
	};

}
