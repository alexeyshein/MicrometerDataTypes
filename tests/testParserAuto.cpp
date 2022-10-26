#include "catch.hpp"
#include <fstream>
#include "ParserAuto.h"

TEST_CASE_METHOD(rf::ParserAuto, "ParserAuto/ Write-Read", "[create]")
{

    const std::deque<rf::Point2d<double>> contPoints1{
        {-25.0, 20.0}, {-25.0, -20.0}, {25.0, -20}, {25.0, 20}};
    const rf::Contour cont1(0, contPoints1, rf::ContourType::Outer);

    const std::deque<rf::Point2d<double>> contPoints2{
        {0.0, 5.0},{10.0,0.0},{0.0, -5.0}, {-10.0, 0.0},};
    const rf::Contour cont2(0, contPoints2, rf::ContourType::Inner);

   
    rf::Profile profile(0,111,{cont1, cont2}, {-1, 0});

    SECTION(".csv")
    {
        std::string path = "1/2/3/testAuto.csv";
        Save(profile, path);
        rf::Profile read{};
        Read(read, path);
        
        const auto& contoursEt = profile.ContoursConstRef();
        const auto& contoursRead = read.ContoursConstRef();
        REQUIRE(contoursEt.size() == contoursRead.size());

        if(contoursRead.at(0).GetContourType()==rf::ContourType::Outer)
        {
            REQUIRE(contoursRead.at(1).GetContourType()==rf::ContourType::Inner);
            REQUIRE(read.HierarchyConstRef().at(0)==-1);
            REQUIRE(read.HierarchyConstRef().at(1)==0);
        }else{
            REQUIRE(contoursRead.at(1).GetContourType()==rf::ContourType::Outer);
            REQUIRE(read.HierarchyConstRef().at(1)==-1);
            REQUIRE(read.HierarchyConstRef().at(0)==0);
        }
    }

    SECTION(".dxf")
    {
        std::string path = "1/2/3/testAuto.dxf";
        Save(profile, path);
        rf::Profile read{};
        Read(read, path);
        
        const auto& contoursEt = profile.ContoursConstRef();
        const auto& contoursRead = read.ContoursConstRef();
        REQUIRE(contoursEt.size() == contoursRead.size());

        if(contoursRead.at(0).GetContourType()==rf::ContourType::Outer)
        {
            REQUIRE(contoursRead.at(1).GetContourType()==rf::ContourType::Inner);
            REQUIRE(read.HierarchyConstRef().at(0)==-1);
            REQUIRE(read.HierarchyConstRef().at(1)==0);
        }else{
            REQUIRE(contoursRead.at(1).GetContourType()==rf::ContourType::Outer);
            REQUIRE(read.HierarchyConstRef().at(1)==-1);
            REQUIRE(read.HierarchyConstRef().at(0)==0);
        }
    }

}
