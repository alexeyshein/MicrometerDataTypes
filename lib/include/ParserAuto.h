#pragma once

#include "IProfileParser.h"
#include <memory>
#include <vector>
#include <Profile.h>
#include <Contour.h>

namespace rf
{
class ParserAuto : public IProfileParser
{
public:
    ParserAuto();
    virtual ~ParserAuto();
    bool Save(const Profile& profile, const std::string &path) override;
    bool Read(Profile& profile, const std::string &path) override;
    bool IsFileTypeCorrect(const std::string& path) override;

    
private:
    IProfileParser* GetParser(const std::string& path);
private:
    std::vector<std::unique_ptr<IProfileParser>> parsers;
};
} // namespace rf
