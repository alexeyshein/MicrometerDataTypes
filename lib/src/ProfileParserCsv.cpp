#include "ProfileParserCsv.h"
#include <filesystem>
#include <sstream>
#include <fstream>
#include <string>

using namespace rf;
namespace fs = std::filesystem;

ProfileParserCsv::ProfileParserCsv() : delimeter{";"}
{
}

ProfileParserCsv::~ProfileParserCsv()
{
}

bool ProfileParserCsv::Save(const Profile& profile, const std::string &pathStr)
{
   const auto &contoursVec = profile.ContoursConstRef();
   const auto &hierarchyVec = profile.HierarchyConstRef();

   std::fstream myfile;
   fs::path path(pathStr);
   fs::path parentPath = path.parent_path();
   //fs::path file = path.filename();

   if (!fs::exists(parentPath))
   {
      fs::create_directories(parentPath);
   }

   myfile.open(pathStr, std::fstream::out | std::fstream::trunc);
   if (!myfile.is_open())
      return false;

   for (int i = 0; i < contoursVec.size(); ++i)
   {
      const auto &contourPoints = contoursVec.at(i).PointsConstRef();
      auto parentIndex = -1;
      if(hierarchyVec.size()>i)  //если вектор иерархий заполнен
         parentIndex = hierarchyVec.at(i);
      for (const auto &point : contourPoints)
      {
         myfile << i + 1 << delimeter << point.x << delimeter << point.y << delimeter << parentIndex<< std::endl;
      }
   }
   myfile.close();
   return true;
}

bool ProfileParserCsv::Read(Profile& profile, const std::string &path)
{

   std::fstream myfile;
   Profile tmpProfile{};
   //auto 
   std::vector<std::deque<Point2d<double>>> tmpProfiles{};
   myfile.open(path, std::fstream::in);
   if (!myfile.is_open())
   {
      return false;
   }

   std::string line;
   int numPrev {1};
   std::deque<Point2d<double>> curContour;
   while (!myfile.eof())
   {
      std::getline(myfile, line);
      if (line.empty())
         continue;
      std::istringstream ss(line);
      std::string token{};
      int num=numPrev;
      double x{0.0};
      double y{0.0};
      try
      {
         std::getline(ss, token, delimeter[0]);
         num = std::stoi(token);
         std::getline(ss, token, delimeter[0]);
         x = std::stod(token);
         std::getline(ss, token, delimeter[0]);
         y = std::stod(token);
      }
      catch (const std::invalid_argument& ia) {
        //std::cerr << "Invalid argument: " << ia.what() << std::endl;
        continue;
      }
      catch (const std::out_of_range& oor) {
        //std::cerr << "Out of Range error: " << oor.what() << std::endl;
        continue;
      }
      catch (const std::exception& e)
      {
        //std::cerr << "Undefined error: " << e.what() << std::endl;
        continue;
      }
      if (num != numPrev)
      {
         //Start new profile
         tmpProfiles.push_back(curContour);
         curContour.clear();
      }
      numPrev = num;
      curContour.push_back({x, y});
   }
   tmpProfiles.push_back(curContour);
   //profiles = std::move(tmpProfiles); TMP
   myfile.close();
   return true;
}
