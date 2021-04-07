#include <iostream>
#include "Contour.h"


using rf::Contour;
using rf::ContourType;


Contour::Contour( uint64_t id_):
  id(id_)
{};

Contour::Contour( uint64_t id_, const std::deque<Point2d<double>>& points_, ContourType type):
  id(id_)
, points(points_)
, contourType(type)
{}

Contour::Contour( uint64_t id_, const std::deque<Point2d<double>>&& points_, ContourType type):
  id(id_)
, points(points_)
, contourType(type)
{}

void Contour::Set(uint64_t id_,  const std::deque<Point2d<double>>& points_, ContourType type)
{
  id = id_;
  points = points_;
  contourType = type;
}

void Contour::Set(uint64_t id_,   const std::deque<Point2d<double>>&& points_, ContourType type)
{
  id = id_;
  points = points_;
  contourType = type;
  //TODO посмотреть по Emplace
  //profileQue.emplace(profileQue.end(), std::move(profile));
}

void Contour::SetPoints(const std::vector<Point2d<double>>& pointsVec)
{
  points.clear();
  points.insert(points.end(), std::make_move_iterator( pointsVec.begin() ),
    std::make_move_iterator( pointsVec.end() ));
  }
