#pragma once

#include <vector>
#include <deque>
#include <string>
#include <memory>

#include "IData.h"
#include "Point2d.h"

namespace rf
{


class Polyline: public IData
{
public:
	Polyline( uint64_t id=0);
    Polyline( uint64_t id, const std::vector<Point2d<double>>& polyline);
    Polyline( uint64_t id, const std::vector<Point2d<double>>&& polyline);
	~Polyline() {};
    void Set(uint64_t id,   const std::vector<Point2d<double>>& polyline);
    void Set(uint64_t id,   const std::vector<Point2d<double>>&& polyline);
    uint64_t Id() const override {return id;}   
    const std::vector<Point2d<double>>& ProfileConstRef()  const  {return polyline;}
    std::vector<Point2d<double>>& ProfileRef()   {return polyline;}
protected:

private:
    uint64_t id;
    std::vector<Point2d<double>> polyline;
};

}

