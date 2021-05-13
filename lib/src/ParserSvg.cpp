#include "ParserSvg.h"
#include <filesystem>
#include <sstream>
#include <fstream>
#include <string>

using namespace rf;
namespace fs = std::filesystem;

ParserSvg::ParserSvg() : delimeter{";"}
{
}

ParserSvg::~ParserSvg()
{
}

bool ParserSvg::Save(const Profile& profile, const std::string &pathStr)
{
   const auto &contoursVec = profile.ContoursConstRef();
   const auto &hierarchyVec = profile.HierarchyConstRef();

   std::fstream myFile;
   fs::path path(pathStr);
   fs::path parentPath = path.parent_path();
   //fs::path file = path.filename();

   if (!fs::exists(parentPath))
   {
      fs::create_directories(parentPath);
   }

   myFile.open(pathStr, std::fstream::out | std::fstream::trunc);
   if (!myFile.is_open())
      return false;

   myFile<< "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>"<<std::endl;
   myFile<<"<svg version=\"1.1\"\n \
     baseProfile=\"full\"\n \
     xmlns=\"http://www.w3.org/2000/svg\"\n \
     xmlns:xlink=\"http://www.w3.org/1999/xlink\"\n \
     xmlns:ev=\"http://www.w3.org/2001/xml-events\"\n \
     width=\"50\" height=\"50\">"<<std::endl;
    //myFile<<"<g transform=\"translate(25,25)\">";
   for (int i = 0; i < contoursVec.size(); ++i)
   {
      const auto &contourPoints = contoursVec.at(i).PointsConstRef();
      myFile<<"<polygon points=\"";
      for (const auto &point : contourPoints)
      {
         myFile  << point.x <<","<< point.y<<" ";
      }
      auto type = static_cast<int>(contoursVec.at(i).GetContourType());
      myFile<<"\" ";
      if(type == 0)
         myFile<<"fill=\"gray\" ";
      else
          myFile<<"fill=\"white\" ";

      myFile<<"fill-opacity=\"1.0\"  stroke=\"blue\"  stroke-opacity=\"0.8\"/>"<<std::endl;
   }
       //  myFile<<"</g>"<<std::endl;
      myFile<<"</svg>"<<std::endl;
   myFile.close();
   return true;
}

bool ParserSvg::Read(Profile& profile, const std::string &path)
{
     return false;
}


bool ParserSvg::Save(const Contour& contour, const std::string &pathStr)
{
   return false;
}


bool ParserSvg::Read(Contour& contour, const std::string &path)
{
return false;
}