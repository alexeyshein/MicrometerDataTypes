#pragma once

#include "IProfileParser.h"
#include <Profile.h>
#include <Contour.h>

namespace rf
{
class ProfileParserCsv : public IProfileParser
{
public:
    ProfileParserCsv();
    virtual ~ProfileParserCsv();
    bool Save(const Profile& profile, const std::string &path);
    bool Read(Profile& profile, const std::string &path);
    
    bool Save(const Contour& contour, const std::string &path);
    bool Read(Contour& contour, const std::string &path);
private:
    std::string delimeter;
};
} // namespace rf
