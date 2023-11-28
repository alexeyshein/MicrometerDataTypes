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
    Profile();
	Profile( uint64_t id, uint64_t timestamp);
    Profile( uint64_t id, uint64_t timestamp, const std::vector<Contour>& contours, const std::vector<int>& hierarchy);
    Profile( uint64_t id, uint64_t timestamp, const std::vector<Contour>&& contours, const std::vector<int>&& hierarchy);
	~Profile() = default;
    void Set(uint64_t id, uint64_t timestamp,  const std::vector<Contour>& contours, const std::vector<int>& hierarchy);
    void Set(uint64_t id, uint64_t timestamp,  const std::vector<Contour>&& contours, const std::vector<int>&& hierarchy);
    uint64_t Id()  const  override {return id;}   
    uint64_t Timestamp() const {return  timestamp;}
    void SetId(uint64_t id_){id = id_;}
    void SetTimestamp(uint64_t timestamp_){timestamp = timestamp_;}
    void SetContours(const std::vector<Contour>& contours_){contours = contours_;}
    void SetHierarchy(std::vector<int>& hierarchy_){hierarchy = hierarchy_;}
    void SetContours(const std::vector<Contour>&& contours_){contours = std::move(contours_);}
    void SetHierarchy(std::vector<int>&& hierarchy_){hierarchy = std::move(hierarchy_);}
    const std::vector<Contour>& ContoursConstRef()  const  {return contours;}
    const std::vector<int>& HierarchyConstRef()  const  {return hierarchy;}
    std::vector<Contour>& ContoursRef()   {return contours;}
    std::vector<int>& HierarchyRef()    {return hierarchy;}

protected:

private:
    uint64_t id;
    uint64_t timestamp;
    std::vector<Contour> contours;
    std::vector<int> hierarchy;
};

}

