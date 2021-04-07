#include "ParserCsv.h"
#include <filesystem>
#include <sstream>
#include <fstream>
#include <string>

using namespace rf;
namespace fs = std::filesystem;

ParserCsv::ParserCsv() : delimeter{";"}
{
}

ParserCsv::~ParserCsv()
{
}

bool ParserCsv::Save(const Profile& profile, const std::string &pathStr)
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

   for (int i = 0; i < contoursVec.size(); ++i)
   {
      const auto &contourPoints = contoursVec.at(i).PointsConstRef();
      auto parentIndex = -1;
      if(hierarchyVec.size()>i)  //если вектор иерархий заполнен
         parentIndex = hierarchyVec.at(i);
      for (const auto &point : contourPoints)
      {
         myFile << i + 1 << delimeter << point.x << delimeter << point.y << delimeter << parentIndex<< std::endl;
      }
   }
   myFile.close();
   return true;
}

bool ParserCsv::Read(Profile& profile, const std::string &path)
{
   auto& contours = profile.ContoursRef();
   auto& hierarchy =  profile.HierarchyRef();
   contours.clear();
   hierarchy.clear();
   
   std::fstream myFile;
   //auto 
   myFile.open(path, std::fstream::in);
   if (!myFile.is_open())
   {
      return false;
   }

   std::string line;
   int numPrev {1};
   int parentIndexPrev{1};
   Contour tmpContour;
   auto& points = tmpContour.PointsRef();

   while (!myFile.eof())
   {
      std::getline(myFile, line);
      if (line.empty())
         continue;
      std::istringstream ss(line);
      std::string token{};
      int num=numPrev;
      double x{0.0};
      double y{0.0};
      int parentIndex{-1};
      try
      {
         std::getline(ss, token, delimeter[0]);
         num = std::stoi(token);
         std::getline(ss, token, delimeter[0]);
         x = std::stod(token);
         std::getline(ss, token, delimeter[0]);
         y = std::stod(token);
      }
      catch (const std::invalid_argument&) {
        //std::cerr << "Invalid argument: " << ia.what() << std::endl;
        continue;
      }
      catch (const std::out_of_range&) {
        //std::cerr << "Out of Range error: " << oor.what() << std::endl;
        continue;
      }
      catch (const std::exception&)
      {
        //std::cerr << "Undefined error: " << e.what() << std::endl;
        continue;
      }
      
      try{
         std::getline(ss, token, delimeter[0]);
         parentIndex = std::stoi(token);
      }
      catch (const std::exception&)
      {
        //std::cerr << "Undefined error: " << e.what() << std::endl;
      }
      if (num != numPrev)
      {
         //Start new profile
         if(numPrev == parentIndexPrev)
            tmpContour.SetContourType(ContourType::Outer);
         else
            tmpContour.SetContourType(ContourType::Inner);

         contours.push_back(tmpContour);
         hierarchy.push_back(parentIndexPrev);
         points.clear();
      }

      numPrev = num;
      parentIndexPrev = parentIndex;
      points.push_back({x, y});
   }
   myFile.close();
   return true;
}


bool ParserCsv::Save(const Contour& contour, const std::string &pathStr)
{
   const auto &points = contour.PointsConstRef();
   const int typeInt = static_cast<const int>(contour.GetContourType());

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

   for (const auto &point : points)
   {
      myFile << 1 << delimeter << point.x << delimeter << point.y<< delimeter << typeInt << std::endl;
   }

   myFile.close();
   return true;
}


bool ParserCsv::Read(Contour& contour, const std::string &path)
{
   auto& points = contour.PointsRef();
   points.clear();
   
   std::fstream myFile;
   //auto 
   myFile.open(path, std::fstream::in);
   if (!myFile.is_open())
   {
      return false;
   }

   std::string line;
   int typeInt{-1};
   while (!myFile.eof())
   {
      std::getline(myFile, line);
      if (line.empty())
         continue;
      std::istringstream ss(line);
      std::string token{};
      int num{-1};
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
         std::getline(ss, token, delimeter[0]);
         typeInt = std::stoi(token);
      }
      catch (const std::invalid_argument&) {
        //std::cerr << "Invalid argument: " << ia.what() << std::endl;
        continue;
      }
      catch (const std::out_of_range&) {
        //std::cerr << "Out of Range error: " << oor.what() << std::endl;
        continue;
      }
      catch (const std::exception&)
      {
        //std::cerr << "Undefined error: " << e.what() << std::endl;
        continue;
      }
      
      points.push_back({x, y});
   }

   contour.SetContourType(static_cast<ContourType>(typeInt));

   myFile.close();
   return true;
}