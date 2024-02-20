#include <iostream>
#include "Polyline.h"


using rf::PolyLine;


PolyLine::PolyLine( uint64_t id_):
  id(id_)
{};

PolyLine::PolyLine( uint64_t id_, const std::vector<Point2d<double>>& polyline_):
  id(id_)
, polyline(polyline_)
{}

PolyLine::PolyLine( uint64_t id_,  const std::vector<Point2d<double>>&& polyline_):
  id(id_)
, polyline(polyline_)
{}

void PolyLine::Set(uint64_t id_,  const std::vector<Point2d<double>>& polyline_)
{
  id = id_;
  polyline = polyline_;
}

void PolyLine::Set(uint64_t id_,  const std::vector<Point2d<double>>&& polyline_)
{
  id = id_;
  polyline.clear();
  polyline = polyline_;
  //TODO посмотреть по Emplace
  //profileQue.emplace(profileQue.end(), std::move(profile));
}