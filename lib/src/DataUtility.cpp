#include "DataUtility.h"
#include "Contour.h"
#include <algorithm>

using namespace rf;


// >0 - counterclockwise angle
// <0 - clockwise angle
double getArea(const std::deque<rf::Point2d<double>>& in_points)
{
    double res{0.0};
    int lpt, flag;
    double a00;                 /* unnormalized moments  */
    double xi, yi, xi_1, yi_1, x0, y0, dxy;

    res = 0;
    if (in_points.size() == 0)
        return true;

    lpt = in_points.size();
    a00 = x0 = y0 = xi_1 = yi_1 = 0;
    flag = 0;

    for (int i = 0; i < in_points.size(); ++i)
    {
        if ( flag == 0 )
        {
            xi_1 = in_points[i].x;
            yi_1 = in_points[i].y;
            x0 = xi_1;
            y0 = yi_1;
            flag = 1;
        }
        else
        {
            xi = in_points[i].x;
            yi = in_points[i].y;
            dxy = xi_1 * yi - xi * yi_1;
            a00 += dxy;

            xi_1 = xi;
            yi_1 = yi;
        }
    }

    xi = x0;
    yi = y0;
    dxy = xi_1 * yi - xi * yi_1;

    a00 += dxy;

    res = a00 ;/// 2.;
    return res;
}

// if false then need to reverse
bool DataUtility::CheckIsContourDirectionCorrect(const rf::Contour& contour)
{
     const auto& points = contour.PointsConstRef();
     double area = getArea(points);
     return (area>=0 && contour.GetContourType()==rf::ContourType::Outer) || (area <= 0 && contour.GetContourType()==rf::ContourType::Inner);
}

 
 // Corrects the contour direction if it is not correct for the given type of contour
 void DataUtility::ReverseIfContourWrongDirection(Contour& contour)
 {
   if(!DataUtility::CheckIsContourDirectionCorrect(contour))
   {
      // invert points loop direction
      auto& points = contour.PointsRef();
      reverse(points.begin(), points.end());
   }
 }