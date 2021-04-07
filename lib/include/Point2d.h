#pragma once


namespace rf
{

template<typename T>
struct Point2d
{
	T x;
	T y;
	Point2d() {};
	Point2d(T _x, T _y):
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
};
}

