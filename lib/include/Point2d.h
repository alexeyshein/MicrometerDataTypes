#pragma once

#include <cmath>

namespace rf
{

template<typename _Tp>
struct Point2d
{
	_Tp x;
	_Tp y;
	Point2d() {};
	Point2d(_Tp _x, _Tp _y):
		x (_x)
	,   y(_y)
	{}
	~Point2d() {}

	bool operator ==(const Point2d &other){
       return (x==other.x) && (y==other.y);
	}
	bool operator !=(const Point2d &other){
       return (x!=other.x) || (y!=other.y);
	}
	//! dot product
    _Tp dot(const Point2d& pt) const;
    //! dot product computed in double-precision arithmetics
    double ddot(const Point2d& pt) const;
    //! cross-product
    double cross(const Point2d& pt) const;
};


template<typename _Tp> inline
_Tp Point2d<_Tp>::dot(const Point2d& pt) const
{
    return static_cast<_Tp>(x*pt.x + y*pt.y);
}

template<typename _Tp> inline
double Point2d<_Tp>::ddot(const Point2d& pt) const
{
    return (double)x*(double)(pt.x) + (double)y*(double)(pt.y);
}

template<typename _Tp> inline
double Point2d<_Tp>::cross(const Point2d& pt) const
{
    return (double)x*pt.y - (double)y*pt.x;
}

template<typename _Tp> static inline
Point2d<_Tp>& operator += (Point2d<_Tp>& a, const Point2d<_Tp>& b)
{
    a.x += b.x;
    a.y += b.y;
    return a;
}

template<typename _Tp> static inline
Point2d<_Tp>& operator -= (Point2d<_Tp>& a, const Point2d<_Tp>& b)
{
    a.x -= b.x;
    a.y -= b.y;
    return a;
}

template<typename _Tp> static inline
Point2d<_Tp>& operator *= (Point2d<_Tp>& a, int b)
{
    a.x = static_cast<_Tp>(a.x * b);
    a.y = static_cast<_Tp>(a.y * b);
    return a;
}
template<typename _Tp> static inline
Point2d<_Tp>& operator *= (Point2d<_Tp>& a, float b)
{
    a.x = static_cast<_Tp>(a.x * b);
    a.y = static_cast<_Tp>(a.y * b);
    return a;
}

template<typename _Tp> static inline
Point2d<_Tp>& operator *= (Point2d<_Tp>& a, double b)
{
    a.x = static_cast<_Tp>(a.x * b);
    a.y = static_cast<_Tp>(a.y * b);
    return a;
}

template<typename _Tp> static inline
Point2d<_Tp>& operator /= (Point2d<_Tp>& a, int b)
{
    a.x = static_cast<_Tp>(a.x / b);
    a.y = static_cast<_Tp>(a.y / b);
    return a;
}

template<typename _Tp> static inline
Point2d<_Tp>& operator /= (Point2d<_Tp>& a, float b)
{
    a.x = static_cast<_Tp>(a.x / b);
    a.y = static_cast<_Tp>(a.y / b);
    return a;
}

template<typename _Tp> static inline
Point2d<_Tp>& operator /= (Point2d<_Tp>& a, double b)
{
    a.x = static_cast<_Tp>(a.x / b);
    a.y = static_cast<_Tp>(a.y / b);
    return a;
}


template<typename _Tp> static inline
double norm(const Point2d<_Tp>& pt)
{
    return std::sqrt((double)pt.x*pt.x + (double)pt.y*pt.y);
}

template<typename _Tp> static inline
bool operator == (const Point2d<_Tp>& a, const Point2d<_Tp>& b)
{
    return a.x == b.x && a.y == b.y;
}

template<typename _Tp> static inline
bool operator != (const Point2d<_Tp>& a, const Point2d<_Tp>& b)
{
    return a.x != b.x || a.y != b.y;
}

template<typename _Tp> static inline
Point2d<_Tp> operator + (const Point2d<_Tp>& a, const Point2d<_Tp>& b)
{
    return Point2d<_Tp>( static_cast<_Tp>(a.x + b.x), static_cast<_Tp>(a.y + b.y) );
}

template<typename _Tp> static inline
Point2d<_Tp> operator - (const Point2d<_Tp>& a, const Point2d<_Tp>& b)
{
    return Point2d<_Tp>( static_cast<_Tp>(a.x - b.x), static_cast<_Tp>(a.y - b.y) );
}

template<typename _Tp> static inline
Point2d<_Tp> operator - (const Point2d<_Tp>& a)
{
    return Point2d<_Tp>( static_cast<_Tp>(-a.x), static_cast<_Tp>(-a.y) );
}

template<typename _Tp> static inline
Point2d<_Tp> operator * (const Point2d<_Tp>& a, int b)
{
    return Point2d<_Tp>( static_cast<_Tp>(a.x*b), static_cast<_Tp>(a.y*b) );
}

template<typename _Tp> static inline
Point2d<_Tp> operator * (int a, const Point2d<_Tp>& b)
{
    return Point2d<_Tp>( static_cast<_Tp>(b.x*a), static_cast<_Tp>(b.y*a) );
}

template<typename _Tp> static inline
Point2d<_Tp> operator * (const Point2d<_Tp>& a, float b)
{
    return Point2d<_Tp>( static_cast<_Tp>(a.x*b), static_cast<_Tp>(a.y*b) );
}

template<typename _Tp> static inline
Point2d<_Tp> operator * (float a, const Point2d<_Tp>& b)
{
    return Point2d<_Tp>( static_cast<_Tp>(b.x*a), static_cast<_Tp>(b.y*a) );
}

template<typename _Tp> static inline
Point2d<_Tp> operator * (const Point2d<_Tp>& a, double b)
{
    return Point2d<_Tp>( static_cast<_Tp>(a.x*b), static_cast<_Tp>(a.y*b) );
}

template<typename _Tp> static inline
Point2d<_Tp> operator * (double a, const Point2d<_Tp>& b)
{
    return Point2d<_Tp>( static_cast<_Tp>(b.x*a), static_cast<_Tp>(b.y*a) );
}


template<typename _Tp> static inline
Point2d<_Tp> operator / (const Point2d<_Tp>& a, int b)
{
    Point2d<_Tp> tmp(a);
    tmp /= b;
    return tmp;
}

template<typename _Tp> static inline
Point2d<_Tp> operator / (const Point2d<_Tp>& a, float b)
{
    Point2d<_Tp> tmp(a);
    tmp /= b;
    return tmp;
}

template<typename _Tp> static inline
Point2d<_Tp> operator / (const Point2d<_Tp>& a, double b)
{
    Point2d<_Tp> tmp(a);
    tmp /= b;
    return tmp;
}
}

