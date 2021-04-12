#pragma once

#include "Point2d.h"

namespace rf
{
	class SegmentLine
	{
	public:
		SegmentLine():
		point1(0.0, 0.0)
		,point2(1.0, 1.0)
        {}

		SegmentLine(const Point2d<double>& point1_, const Point2d<double>& point2_):
		   point1(point1_)
		,  point2(point2_)
		{}

		~SegmentLine() {}

        void  Set(const Point2d<double>& point1_, const Point2d<double>& point2_)
		{
			point1 = point1_;
		    point2 = point2_;
		}

		void  Point1(const Point2d<double>& point1_)  { point1 = point1_; }
		void  Point2(const Point2d<double>& point2_) { point2 = point2_; }

		Point2d<double> Point1() const  { return point1; }
		Point2d<double> Point2() const  { return point2; }

	private:
		Point2d<double> point1;
		Point2d<double> point2;
		
	};

}
