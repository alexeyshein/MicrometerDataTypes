#pragma once

#include "IProfileParser.h"
#include <Profile.h>
#include <Contour.h>

namespace rf
{
class ParserDxf : public IProfileParser
{
public:
    ParserDxf();
    virtual ~ParserDxf();
    bool Save(const Profile& profile, const std::string &path) override;
    bool Read(Profile& profile, const std::string &path) override;
    
    bool Save(const Contour& contour, const std::string &path);
    bool Read(Contour& contour, const std::string &path);
private:
    std::string delimeter;
};
} // namespace rf
