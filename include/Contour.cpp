#include <iostream>
#include "Contour.h"


using rf::Contour;
using rf::ContourType;


Contour::Contour( uint64_t id_):
  id(id_)
{};

Contour::Contour( uint64_t id_, const std::deque<Point2d<double>>& contour_, ContourType type):
  id(id_)
, contour(contour_)
, contourType(type)
{}

Contour::Contour( uint64_t id_, const std::deque<Point2d<double>>&& contour_, ContourType type):
  id(id_)
, contour(contour)
, contourType(type)
{}

void Contour::Set(uint64_t id_,  const std::deque<Point2d<double>>& contour_, ContourType type)
{
  id = id_;
  contour = contour_;
  contourType = type;
}

void Contour::Set(uint64_t id_,   const std::deque<Point2d<double>>&& contour_, ContourType type)
{
  id = id_;
  contour = contour_;
  contourType = type;
  //TODO посмотреть по Emplace
  //profileQue.emplace(profileQue.end(), std::move(profile));
}