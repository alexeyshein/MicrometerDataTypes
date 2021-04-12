#pragma once

#include "Point2d.h"
#include <cmath>

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

	StraightLine::StraightLine() : a(1.0), b(1.0), c(0.0)
	{
	}

	StraightLine::StraightLine(double a_, double b_, double c_)
		: a(a_), b(b_), c(c_)
	{
	}

	StraightLine::StraightLine(double k, double b) : StraightLine(-k, 1.0, -b)
	{
		double l = std::pow(a * a + b * b, 0.5);
		a /= l;
		b /= l;
		c /= l;
	}
    
	StraightLine::StraightLine(const Point2d<double>& point1, const Point2d<double>& point2)
	{
         Set(point1, point2);
	}


	void StraightLine::Set(double a_, double b_, double c_)
	{
		a = a;
		b = b;
		c = c;
	}

	void StraightLine::Set(double k, double b)
	{
		double nA{-k};
		double nB{1.0};
		double nC{ -b};
		double l = std::pow(nA * nA + nB * nB, 0.5);
		a = nA / l;
		b = nB / l;
		c = nC / l;
	}
     
	void StraightLine::Set(const Point2d<double>& point1, const Point2d<double>& point2)
	{
		// http://www.math.by/geometry/eqline.html
       	a = point1.y - point2.y;
		b = point2.x - point1.x;
		c = point1.x*point2.y - point2.x*point1.y;
	}
 
	// Calculates y by given x coordinate of point
	double StraightLine::yByX(double x) const
	{
         return (a*x + c) / (-b);
	}
	
	// Calculates x by given y coordinate of point
	double StraightLine::xByY(double y) const
	{
        return (b*y + c) / (-a);
	}

