#include "catch.hpp"
#include <fstream>
#include "ParserCsv.h"

TEST_CASE_METHOD(rf::ParserCsv, "ParserCsv/ Write-Read", "[create]")
{
    //Have right to protected member`s of class rf::ContoursFinderSuzuki

    const std::deque<rf::Point2d<double>> contPoints1{
        {1.1, 1.2}};
    const rf::Contour cont1(0, contPoints1, rf::ContourType::Inner);
    const std::deque<rf::Point2d<double>> contPoints2{
        {2.0, 1.2}, {2.0, 2.2}, {2.0, 3.2}, {2.0, 4.2}};
    const rf::Contour cont2(0, contPoints1, rf::ContourType::Outer);

    std::string path = "1/2/3/test.csv";

    SECTION("Contours Count and sizes ")
    {
        rf::Profile profile(0,111,{cont1, cont2}, {0, 1});
        Save(profile, path);
        rf::Profile read{};
        Read(read, path);

        // REQUIRE(profile.ProfileConstRef().size() == read.ProfileConstRef().size());
        // for (int i = 0; i < profile.ProfileConstRef().size(); ++i)
        // {
        //     REQUIRE(contours.at(i).size() == read.at(i).size());
        // }
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
