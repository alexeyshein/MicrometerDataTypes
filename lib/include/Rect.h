#pragma once

#include "Point2d.h"

namespace rf
{

class Rect
{
	public:

	Rect();
	Rect(const Point2d<double>& pointTl, double width, double height);
	Rect(const Point2d<double>& point1, const Point2d<double>& point2);

	~Rect() {}
   
    void Set(const Point2d<double>& point1, const Point2d<double>& point2);
	void Set(const Point2d<double>& point1, double width, double height);
	void SetWidth(double width_){width_ = width_;}
	void SetHeight(double height_){height = height_;}
	
	Point2d<double> PointTl()const {return pointTl;};
	double Width() const {return width;}
	double Height() const {return height;}

	private:

    Point2d<double> pointTl; // left-top point
	double width; // right bottom point
	double height;
};

    Rect::Rect():
	  pointTl(0.0, 0.0)
	, width(1.0)
	, height(1.0)
	{}

	Rect::Rect(const Point2d<double>& point1, const Point2d<double>& point2)
	{
      Set(point1, point2);
	}

	Rect::Rect(const Point2d<double>& pointTl_, double width_, double height_):
	  pointTl(pointTl_)
	, width(width_)
	, height(height_)
	{
	};
   
    void Rect::Set(const Point2d<double>& point1, const Point2d<double>& point2)
	{
	//Rect от меньшего к большему
	pointTl.x = point1.x;
    width = point2.x - point1.x;
    if (width<0)
    {
        pointTl.x = point2.x;
		width = -width;
    }
  
	pointTl.y =  point1.y;
    height = point2.y - point1.y;
    if (height<0)
    {
        pointTl.y = point2.y;
		height = -height;
    }
	}

	void Rect::Set(const Point2d<double>& pointTl_, double width_, double height_)
	{
	pointTl = 	pointTl_;
	width = width_;
	height = height_;
	}

	}

