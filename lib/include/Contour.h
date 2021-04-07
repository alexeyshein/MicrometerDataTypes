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
    Contour( uint64_t id, const std::deque<Point2d<double>>& points,  ContourType type);
    Contour( uint64_t id, const std::deque<Point2d<double>>&& points,  ContourType type);
	~Contour() {};
    void Set(uint64_t id,  const std::deque<Point2d<double>>& points,  ContourType type);
    void Set(uint64_t id,  const std::deque<Point2d<double>>&& points,  ContourType type);
    uint64_t Id() const override {return id;}
    void SetId(uint64_t id_){id = id_;}
    ContourType GetContourType() const {return  contourType;}
    void SetContourType(ContourType contourType_){contourType = contourType_;}
    const std::deque<Point2d<double>>& PointsConstRef()  const  {return points;}
    std::deque<Point2d<double>>& PointsRef()   {return points;}
    void SetPoints(const std::deque<Point2d<double>>& points_){points = points_;}
    void SetPoints(const std::deque<Point2d<double>>&& points_){points = std::move(points_);}
    void SetPoints(const std::vector<Point2d<double>>& pointsVec);
    uint32_t Size() const {return static_cast<uint32_t>(points.size());}
protected:

private:
    uint64_t id;
    std::deque<Point2d<double>> points;
    ContourType contourType;
};

}

