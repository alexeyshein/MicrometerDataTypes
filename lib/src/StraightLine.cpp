#include "StraightLine.h"

#include <cmath>
#include <stdexcept> 

using namespace rf;

StraightLine::StraightLine() : a(1.0), b(1.0), c(0.0)
{
}

StraightLine::StraightLine(double a_, double b_, double c_)
	: a(a_), b(b_), c(c_)
{
}

StraightLine::StraightLine(double k, double b) 
{
	Set(k, b);
}

StraightLine::StraightLine(const Point2d<double> &point1, const Point2d<double> &point2)
{
	Set(point1, point2);
}

void StraightLine::Set(double a_, double b_, double c_)
{
	a = a_;
	b = b_;
	c = c_;
	//normalize();
}

void StraightLine::Set(double k, double b_intercept)
{
	// y = kx + b_intercept  -->  k*x - 1*y + b_intercept = 0
	a = k;
	b = -1.0;
	c = b_intercept;
	normalize();
}

void StraightLine::Set(const Point2d<double> &point1, const Point2d<double> &point2)
{
	if (std::sqrt(std::pow(point1.x - point2.x, 2) + std::pow(point1.y - point2.y, 2)) < 1e-9)
	{
		// Option 1: Create an invalid line that can be checked later.
		a = 0.0;
		b = 0.0;
		c = 1.0; // или можно бросить исключение: throw std::invalid_argument("Points are identical.");
		return;
	}

	a = point1.y - point2.y;
	b = point2.x - point1.x;
	c = point1.x * point2.y - point2.x * point1.y;
	normalize();
}

// Calculates y by given x coordinate of point
double StraightLine::yByX(double x) const
{
	const double eps = 1e-10;
	if (std::abs(b) < eps) {
		throw std::runtime_error("Cannot calculate y for vertical line");
	}
	return (a * x + c) / (-b);
}

// Calculates x by given y coordinate of point
double StraightLine::xByY(double y) const
{
	const double eps = 1e-10;
	if (std::abs(a) < eps) {
		throw std::runtime_error("Cannot calculate x for horizontal line");
	}
	return (b * y + c) / (-a);
}

void StraightLine::normalize()
{
	// Не нормализуем, если это невалидная прямая (A=0, B=0)
	if (std::abs(a) < 1e-9 && std::abs(b) < 1e-9) {
		return;
	}

	double l = std::sqrt(a * a + b * b);

	// Дополнительная защита от деления на ноль, если l слишком мало
	if (l > 1e-9) {
		a /= l;
		b /= l;
		c /= l;
	}
}