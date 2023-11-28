#include <iostream>
#include "Profile.h"


using namespace::rf;

Profile::Profile():
 id(0)
, timestamp(0)
, contours(0)
, hierarchy(0)
{
}

Profile::Profile( uint64_t id_, uint64_t timestamp_):
  id(id_)
, timestamp(timestamp_)
{};

Profile::Profile( uint64_t id_, uint64_t timestamp_, const std::vector<Contour>& contours_, const std::vector<int>& hierarchy_):
  id(id_)
, timestamp(timestamp_)
, contours(contours_)
, hierarchy(hierarchy_)
{}

Profile::Profile( uint64_t id_, uint64_t timestamp_, const std::vector<Contour>&& contours_, const std::vector<int>&& hierarchy_):
  id(id_)
, timestamp(timestamp_)
, contours(contours_)
, hierarchy(hierarchy_)
{}

void Profile::Set(uint64_t id_, uint64_t timestamp_,  const std::vector<Contour>& contours_, const std::vector<int>& hierarchy_)
{
  id = id_;
  timestamp = timestamp_;
  contours = contours_;
  hierarchy = hierarchy_;
}

void Profile::Set(uint64_t id_, uint64_t timestamp_,  const std::vector<Contour>&& contours_, const std::vector<int>&& hierarchy_)
{
  id = id_;
  timestamp = timestamp_;
  contours.clear();
  contours = contours_;
  hierarchy = hierarchy_;
  //TODO посмотреть по Emplace
  //profileQue.emplace(profileQue.end(), std::move(profile));
}