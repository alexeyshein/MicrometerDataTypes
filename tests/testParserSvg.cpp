#include "catch.hpp"
#include <fstream>
#include "ParserSvg.h"

TEST_CASE_METHOD(rf::ParserSvg, "ParserSvg/ Write-Read", "[create]")
{
    //Have right to protected member`s of class rf::ContoursFinderSuzuki

    const std::deque<rf::Point2d<double>> contPoints1{
        {0.0, 20.0}, {-25.0, 0.0}, {0.0, -20.0}, {25.0, -0.0}};
    const rf::Contour cont1(0, contPoints1, rf::ContourType::Outer);
    const std::deque<rf::Point2d<double>> contPoints2{
        {-5.0, 5.0}, {5.0, 5.0},{5.0, -5.0}, {-5.0, -5.0} };
    const rf::Contour cont2(0, contPoints2, rf::ContourType::Inner);

    std::string path = "1/2/3/test.svg";

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

}
