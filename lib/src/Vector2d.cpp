#include "Vector2d.h"
#include <math.h>


using rf::Vector2D;


Vector2D::Vector2D() : x(0), y(0)
{
}

Vector2D::Vector2D(double x, double y) : x(x), y(y)
{
}

bool Vector2D::operator==(const Vector2D& vec) const
{
	return (x == vec.x && y == vec.y);
}

Vector2D Vector2D::operator+(const Vector2D& vec) const
{
	return Vector2D(x + vec.x, y + vec.y);
}

void Vector2D::operator+=(const Vector2D& vec)
{
	x += vec.x;
	y += vec.y;
}

Vector2D Vector2D::operator-(const Vector2D& vec) const
{
	return Vector2D(x - vec.x, y - vec.y);
}

void Vector2D::operator-=(const Vector2D& vec)
{
	x -= vec.x;
	y -= vec.y;
}

Vector2D Vector2D::operator*(const double& num) const
{
	return Vector2D(x*num, y*num);
}

void Vector2D::operator*=(const double& num)
{
	x *= num;
	y *= num;
}

Vector2D Vector2D::operator/(const double& num) const
{
	return Vector2D(x / num, y / num);
}

void Vector2D::operator/=(const double& num)
{
	x /= num;
	y /= num;
}

double Vector2D::operator*(const Vector2D& vec) const
{
	return (x*vec.x + y * vec.y);
}

double Vector2D::cross(const Vector2D& vec) const
{
	return (x*vec.y - y * vec.x);
}

double Vector2D::angleWith(const Vector2D& vec) const
{
	return acos(*this * vec / (this->mod() * vec.mod()));
}

double Vector2D::getProjectedLengthTo(const Vector2D& vec) const
{
	return getProjectedLengthToNormalized(vec.getNormalized());
}

double Vector2D::getProjectedLengthToNormalized(const Vector2D& normalizedVec) const
{
	return *this * normalizedVec;
}

Vector2D Vector2D::getProjectedTo(const Vector2D& vec) const
{
	// Is equal to getProjectedToNormalized(vec.getNormalized()),
	// but requires only mod2 without sqrt.
	return vec * ((vec * *this) / vec.mod2());
}

Vector2D Vector2D::getProjectedToNormalized(const Vector2D& normalizedVec) const
{
	// Is equal to getProjectedLengthToNormalized(normalizedVec) * normalizedVec,
	// but requires only mod2 without sqrt.
	return normalizedVec * (normalizedVec * *this);
}

void Vector2D::decompose(const Vector2D& vecA, const Vector2D& vecB,  double& a,  double& b) const
{
	// Matrix22 mat;
	// mat(0, 0) = vecA.x;
	// mat(1, 0) = vecA.y;
	// mat(0, 1) = vecB.x;
	// mat(1, 1) = vecB.y;
	// Matrix21 B(x, y);
	// B = mat.getInversed() * B;
	// a = B(0);
	// b = B(1);
}

void Vector2D::decomposeIntoParPerp(const Vector2D& base,  Vector2D& parallel,  Vector2D& perpendicular) const
{
	parallel = getProjectedTo(base);
	perpendicular = *this - parallel;
}

Vector2D Vector2D::getPerpendicularTo(const Vector2D& vec) const
{
	return *this - getProjectedTo(vec);
}

Vector2D Vector2D::getPerpendicularToNormalized(const Vector2D& vec) const
{
	return *this - getProjectedToNormalized(vec);
}

double Vector2D::mod() const
{
	return sqrt(x*x + y*y);
}

double Vector2D::mod2() const
{
	return (x*x + y*y);
}

Vector2D Vector2D::getNormalized() const
{
	return *this / mod();
}

void Vector2D::normalize()
{
	*this = *this / mod();
}

Vector2D Vector2D::getNormalLeft() const
{
	return Vector2D(-y, x);
}

Vector2D Vector2D::getNormalRight() const
{
	return Vector2D(y, -x);
}

Vector2D Vector2D::getRotatedCW(double angle) const
{
	return getRotatedCCW(-angle);
}

Vector2D Vector2D::getRotatedCCW(double angle) const
{
	return {x*cos(angle) - y*sin(angle), x*sin(angle) + y*cos(angle)};
}

Vector2D Vector2D::operator-() const
{
	return Vector2D(-x, -y);
}

Vector2D operator*(const double& num, const Vector2D& vec)
{
	return vec * num;
}

