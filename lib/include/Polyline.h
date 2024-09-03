#pragma once

#include <vector>

#include "IData.h"
#include "Point2d.h"

namespace rf
{


class PolyLine: public IData
{
public:
    PolyLine( uint64_t id=0);
    PolyLine( uint64_t id, const std::vector<Point2d<double>>& polyline);
    PolyLine( uint64_t id, const std::vector<Point2d<double>>&& polyline);
	~PolyLine() {};
    void Set(uint64_t id,   const std::vector<Point2d<double>>& polyline);
    void Set(uint64_t id,   const std::vector<Point2d<double>>&& polyline);
    uint64_t Id() const override {return id;}   
    const std::vector<Point2d<double>>& PolyLineConstRef()  const  {return polyline;}
    std::vector<Point2d<double>>& PolyLineRef()   {return polyline;}
    size_t Size() const { return polyline.size(); }
protected:

private:
    uint64_t id;
    std::vector<Point2d<double>> polyline;
};

}

