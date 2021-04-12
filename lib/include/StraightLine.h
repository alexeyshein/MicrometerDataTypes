#pragma once

#include "Point2d.h"

namespace rf
{
	class StraightLine
	{
	public:
		StraightLine();
		StraightLine(double a, double b, double c);
		StraightLine(double k, double b);
		StraightLine(const Point2d<double>& point1, const Point2d<double>& point2);

		~StraightLine() {}

		void Set(double a, double b, double c);
		void Set(double k, double b);
        void Set(const Point2d<double>& point1, const Point2d<double>& point2);

		double A() const  { return a; }
		double B() const { return b; }
		double C() const { return c; }

		// Calculates y by given x coordinate of point
		double yByX(double x) const;
		// Calculates x by given y coordinate of point
		double xByY(double y) const;

	private:
		double a;
		double b;
		double c;
	};

}
