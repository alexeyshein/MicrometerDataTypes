#include <iostream>
#include "Polyline.h"


using rf::Polyline;


Polyline::Polyline( uint64_t id_):
  id(id_)
{};

Polyline::Polyline( uint64_t id_, const std::vector<Point2d<double>>& polyline_):
  id(id_)
, polyline(polyline_)
{}

Polyline::Polyline( uint64_t id_,  const std::vector<Point2d<double>>&& polyline_):
  id(id_)
, polyline(polyline_)
{}

void Polyline::Set(uint64_t id_,  const std::vector<Point2d<double>>& polyline_)
{
  id = id_;
  polyline = polyline_;
}

void Polyline::Set(uint64_t id_,  const std::vector<Point2d<double>>&& polyline_)
{
  id = id_;
  polyline.clear();
  polyline = polyline;
  //TODO посмотреть по Emplace
  //profileQue.emplace(profileQue.end(), std::move(profile));
}