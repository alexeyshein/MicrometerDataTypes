#pragma once

#include "IProfileParser.h"
#include <Profile.h>
#include <Contour.h>

namespace rf
{
class ParserCsv : public IProfileParser
{
public:
    ParserCsv();
    virtual ~ParserCsv();
    bool Save(const Profile& profile, const std::string &path);
    bool Read(Profile& profile, const std::string &path);
    
    bool Save(const Contour& contour, const std::string &path);
    bool Read(Contour& contour, const std::string &path);
private:
    std::string delimeter;
};
} // namespace rf
