#pragma once

namespace rf
{

struct Vector2D
{
	double x;
	double y;

	Vector2D();
	Vector2D(double x, double y);

	bool operator==(const Vector2D& vec) const;

	Vector2D operator+(const Vector2D& vec) const;
	void operator+=(const Vector2D& vec);
	Vector2D operator-(const Vector2D& vec) const;
	void operator-=(const Vector2D& vec);
	
	Vector2D operator*(const double& num) const;
	void operator*=(const double& num);
	Vector2D operator/(const double& num) const;
	void operator/=(const double& num);

	double operator*(const Vector2D& vec) const;
	double cross(const Vector2D& vec) const;

	double angleWith(const Vector2D& vec) const;

	double getProjectedLengthTo(const Vector2D& vec) const;
	double getProjectedLengthToNormalized(const Vector2D& normalizedVec) const;

	Vector2D getProjectedTo(const Vector2D& vec) const;
	Vector2D getProjectedToNormalized(const Vector2D& normalizedVec) const;

	// Decomposes vector into two like vec = a * vecA + b * vecB
	void decompose(const Vector2D& vecA, const Vector2D& vecB,  double& a,  double& b) const;
	// Decomposes vector into parallel and perpendicular components based on base vector,
	// i.e. vec = par + perp, and par || base, base * perp = 0
	void decomposeIntoParPerp(const Vector2D& base,  Vector2D& parallel,  Vector2D& perpendicular) const;

	Vector2D getPerpendicularTo(const Vector2D& vec) const;
	Vector2D getPerpendicularToNormalized(const Vector2D& vec) const;

	double mod() const;
	double mod2() const;
	Vector2D getNormalized() const;
	void normalize();

	Vector2D getNormalLeft() const; // Counterclockwise
	Vector2D getNormalRight() const; // Clockwise

	Vector2D getRotatedCW(double angle) const;
	Vector2D getRotatedCCW(double angle) const;

	Vector2D operator-() const;

	friend Vector2D operator*(const double& num, const Vector2D& vec);
};

}