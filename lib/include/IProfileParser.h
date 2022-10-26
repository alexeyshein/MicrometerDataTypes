#pragma once

#include <string>
#include <vector>
#include <deque>

//#include <Profile.h>

namespace rf
{
class Profile;

class IProfileParser
{
public:
    IProfileParser(){};
    virtual bool Save(const Profile& profile, const std::string& path) = 0;
    virtual bool Read(Profile& profile, const std::string& path) = 0 ;
    virtual bool IsFileTypeCorrect(const std::string& path) = 0;
};
}

