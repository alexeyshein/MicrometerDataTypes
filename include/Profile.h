#pragma once

#include <vector>
#include <deque>
#include <string>
#include <memory>

#include "IData.h"
#include "Point2d.h"
#include "Contour.h"

namespace rf
{


class Profile: public IData
{
public:
	Profile( uint64_t id=0, uint64_t timestamp=0);
    Profile( uint64_t id, uint64_t timestamp, const std::vector<Contour>& profileQue, const std::vector<int>& hierarchy);
    Profile( uint64_t id, uint64_t timestamp, const std::vector<Contour>&& profileQue, const std::vector<int>&& hierarchy);
	~Profile() {};
    void Set(uint64_t id, uint64_t timestamp,  const std::vector<Contour>& profileQue, const std::vector<int>& hierarchy);
    void Set(uint64_t id, uint64_t timestamp,  const std::vector<Contour>&& profileQue, const std::vector<int>&& hierarchy);
    uint64_t Id()  const  override {return id;}   
    uint64_t Timestamp() const {return  timestamp;}
    const std::vector<Contour>& ProfileConstRef()  const  {return profile;}
    const std::vector<int>& ProfileHierarchyConstRef()  const  {return hierarchy;}
    std::vector<Contour>& ProfileRef()   {return profile;}
    std::vector<int>& ProfileHierarchyRef()    {return hierarchy;}

protected:

private:
    uint64_t id;
    uint64_t timestamp;
    std::vector<Contour> profile;
    std::vector<int> hierarchy;
};

}

