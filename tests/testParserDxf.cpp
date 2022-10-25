#include "catch.hpp"
#include <fstream>
#include "ParserDxf.h"

TEST_CASE_METHOD(rf::ParserDxf, "ParseDxf/ Write-Read", "[create]")
{
    //Have right to protected member`s of class rf::ContoursFinderSuzuki
    const std::deque<rf::Point2d<double>> contPoints1{
        {-25.0, 20.0}, {-25.0, -20.0}, {25.0, -20}, {25.0, 20}};
    const rf::Contour cont1(0, contPoints1, rf::ContourType::Outer);

    const std::deque<rf::Point2d<double>> contPoints2{
        {0.0, 5.0},{10.0,0.0},{0.0, -5.0}, {-10.0, 0.0},};
    const rf::Contour cont2(0, contPoints2, rf::ContourType::Inner);


    std::string path = "1/2/3/test.dxf";

    SECTION("Contours Count and sizes ")
    {
        rf::Profile profile(0,111,{cont1, cont2}, {-1, 0});
        Save(profile, path);
        rf::Profile read{};
        Read(read, path);
        const auto& contoursEt = profile.ContoursConstRef();
        const auto& contoursRead = read.ContoursConstRef();

        REQUIRE(contoursEt.size() == contoursRead.size());

        for (int i = 0; i < contoursEt.size(); ++i)
        {
            REQUIRE(contoursEt.at(i).Size() == contoursRead.at(i).Size());
        }
    }

    SECTION("Check Points in each contours")
    {
        // std::vector<std::deque<rf::Point2d<double>>> contours{cont1, cont2};
        // Save(contours, path);
        // std::vector<std::deque<rf::Point2d<double>>> read{};
        // Read(read, path);
        // for (int i = 0; i < contours.size(); ++i)
        // {
        //     for (int p = 0; p < contours.at(i).size(); ++p)
        //     {
        //         REQUIRE(contours.at(i).at(p).x == read.at(i).at(p).x);
        //         REQUIRE(contours.at(i).at(p).y == read.at(i).at(p).y);
        //     }
        // }
    }

    SECTION("Check Points in each contours. File with illegal lines ")
    {
        // std::vector<std::deque<rf::Point2d<double>>> contours{cont1, cont2};
        // path = "1/2/3/test2.csv";
        // Save(contours, path);
        // std::fstream myFile;
        // myFile.open(path, std::fstream::in|std::fstream::out|std::fstream::app);
        // myFile<<";;;";
        // myFile<<"####";
        // myFile.close();
        // std::vector<std::deque<rf::Point2d<double>>> read{};
        // Read(read, path);
        // REQUIRE(contours.size() == read.size());
        // for (int i = 0; i < contours.size(); ++i)
        // {
        //     REQUIRE(contours.at(i).size() == read.at(i).size());
        // }
    }
}
