#include "ParserAuto.h"
#include "ParserCsv.h"
#include "ParserDxf.h"
#include "ParserSvg.h"

using namespace rf;

ParserAuto::ParserAuto()
// :
// parsers{
//    //std::make_unique<ParserCsv>()//,
//     std::make_unique<ParserDxf>()//,
//    // std::make_unique<ParserSvg>()
// }
{
   parsers.emplace_back(std::make_unique<ParserCsv>());
   parsers.emplace_back(std::make_unique<ParserDxf>());
   parsers.emplace_back(std::make_unique<ParserSvg>());
}

ParserAuto::~ParserAuto()
{
}

bool ParserAuto::Save(const Profile& profile, const std::string &pathStr)
{
   IProfileParser * parser {GetParser(pathStr)};
   if(!parser)
     return false;
   return parser->Save(profile,pathStr);
}

bool ParserAuto::Read(Profile& profile, const std::string &pathStr)
{
   IProfileParser * parser {GetParser(pathStr)};
   if(!parser)
     return false;
   return parser->Read(profile,pathStr);
}


bool ParserAuto::IsFileTypeCorrect(const std::string& path) 
{
   for(const auto &parser : parsers)
   {
      if(parser->IsFileTypeCorrect(path))
         return true;
   }
   return false;
}

std::set<std::string> ParserAuto::GetSupportedTypes()
{
    std::set<std::string> result;
    for (const auto& parser : parsers)
    {
        auto v{ parser->GetSupportedTypes() };
        result.merge(v);
    }
    return result;
}

 IProfileParser* ParserAuto::GetParser(const std::string& path)
 {
   for(const auto &parser : parsers)
   {
      if(parser->IsFileTypeCorrect(path))
         return parser.get();
   }
   return nullptr;
 }
