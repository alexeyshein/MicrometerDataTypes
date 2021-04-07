#pragma once

#include <vector>
#include <deque>
#include <string>
#include <memory>

#include "IData.h"
#include "Point2d.h"

namespace rf
{
enum class ContourType
{
    Outer = 0,
    Inner
};

class Contour: public IData
{
public:
	Contour( uint64_t id=0);
    Contour( uint64_t id, const std::deque<Point2d<double>>& contour,  ContourType type);
    Contour( uint64_t id, const std::deque<Point2d<double>>&& contour,  ContourType type);
	~Contour() {};
    void Set(uint64_t id,  const std::deque<Point2d<double>>& profileQue,  ContourType type);
    void Set(uint64_t id,  const std::deque<Point2d<double>>&& profileQue,  ContourType type);
    uint64_t Id() const override {return id;}
    ContourType GetContourType() const {return  contourType;}
    const std::deque<Point2d<double>>& ContourConstRef()  const  {return contour;}
    std::deque<Point2d<double>>& ContourRef()   {return contour;}
    uint32_t Size() const {return static_cast<uint32_t>(contour.size());}
protected:

private:
    uint64_t id;
    std::deque<Point2d<double>> contour;
    ContourType contourType;
};

}

