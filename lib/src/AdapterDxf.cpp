/*
 * @file AdapterDxf.cpp
 */

/*****************************************************************************
**  $Id: AdapterDxf.cpp 8865 2008-02-04 18:54:02Z andrew $
**
**  This is part of the dxflib library
**  Copyright (C) 2001 Andrew Mustun
**
**  This program is free software; you can redistribute it and/or modify
**  it under the terms of the GNU Library General Public License as
**  published by the Free Software Foundation.
**
**  This program is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU Library General Public License for more details.
**
**  You should have received a copy of the GNU Library General Public License
**  along with this program; if not, write to the Free Software
**  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
******************************************************************************/

#include "AdapterDxf.h"

#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <iterator>
#include <cmath>
#include "DataUtility.h"
#include "curve.h"
#include "check.h"
#include "evaluate.h"
/**
 * Default constructor.
 */
AdapterDxf::AdapterDxf():
interpolate{true}
, stepInterpolation(0.04)
{

}


void AdapterDxf::addHatch(const DL_HatchData& hatchData)  
{
    //printf("HATCH \n");
    // Новый внешний контур в следующем HatchLoop
    contours.clear(); //all contours
    minXcontours.clear(); // minimal X values for all contours
    numContoursInHatch = hatchData.numLoops;// num contours in hatch
    fillContoursInHatch = 0;// 
};

void AdapterDxf::addHatchLoop(const DL_HatchLoopData& loopInfo) {
    //printf("HATCH LOOP \n");
    numEdgesInCont = loopInfo.numEdges;
    fillEdgesInCont = 0;
    contours.emplace_back(rf::Contour(111)); 
    minXcontours.emplace_back(std::numeric_limits<double>::max()); // minimal X values for all contours
};


void AdapterDxf::addHatchEdge(const DL_HatchEdgeData& edge) {
    //printf("HATCH EDGE \n");
    std::vector<rf::Point2d<double>> pointsNew;
    auto& minX = minXcontours.back();
    switch(edge.type)
    {
        case 1: {
              double n{std::hypot(edge.x2-edge.x1, edge.y2-edge.y1)/stepInterpolation} ;
              if(n<1)
                n = 1;
              double deltaX{(edge.x2-edge.x1)/n};
              double deltaY{(edge.y2-edge.y1)/n};

              for(int i=0;i<n-1; i++)
              {
                double x{edge.x1+deltaX*i};
                pointsNew.push_back({edge.x1+deltaX*i, edge.y1+deltaY*i}); 
                if(minX>edge.x1)
                    minX = edge.x1;
              }
              
              break; 
              }// 1=line
        case 2: // 2=arc
         {
            //printf("Warning EDGE arc \n"); 
            //interpolate arc (cx, cy, radius, angle1, angle2, ccw )
            double alfaSh = stepInterpolation/edge.radius; //angle step
            double angleCur{edge.angle1};
            double angleStop{edge.angle2};
            if(angleStop<angleCur)
               angleStop+=2.0*M_PI;
            // if(edge.ccw)
            // {
            //    if(angleStop<angleCur)
            //      angleStop+=2.0*M_PI;
            // }
            // else
            // {
            //    if(angleStop>angleCur)
            //       angleStop-=2.0*M_PI;
            //    alfaSh = -alfaSh;
            // }
             
            //TODO понять как задавать условие при CW, CCW и при переходе через 2Pi
            while(angleCur <= angleStop)
            {
                double anglCalk{angleCur};
                if(!edge.ccw)
                  anglCalk = 2.0*M_PI-angleCur;
                double x{edge.radius*cos(anglCalk)+edge.cx};
                pointsNew.push_back({x, edge.radius*sin(anglCalk)+edge.cy});
                if(minX > x)
                 minX = x;
                angleCur+=alfaSh;
                if(angleStop - angleCur <  alfaSh*0.995 && angleStop > angleCur )
                {
                    //std::cout<< angleStop - angleCur<<std::endl;
                    angleCur = angleStop;
                }
            }
            break; 
          }
        case 3: // 3=elliptic
         { 
            //cx, cy, mx, my, ratio, angle1, angle2, ccw
            //printf("Warning EDGE elliptic \n"); 
            double alfaSh = stepInterpolation/std::max(edge.mx, edge.my); // TODO it`s not correct for ellipse. angle step
            double angleCur{edge.angle1};
            double angleStop{edge.angle2};
            if(angleStop<angleCur)
               angleStop+=2.0*M_PI;
            double a{std::hypot(edge.mx,edge.my)}; //Length of major axis
            double b{a*edge.ratio}; //Length of minor axis
            double fi{std::atan2(edge.my, edge.mx)};// major axis tilt
            while(angleCur <= angleStop)
            {
                double anglCalk{angleCur};
                if(!edge.ccw)
                  anglCalk = 2.0*M_PI-angleCur;
                double ex{a*cos(anglCalk)};
                double ey{b*sin(anglCalk)};
                double nex {ex*cos(fi) - ey*sin(fi)};
                double ney {ex*sin(fi) + ey*cos(fi)};
                double x{nex+edge.cx};
                pointsNew.push_back({x, ney+edge.cy});
                if(minX > x)
                 minX = x;
                angleCur+=alfaSh;
                if(angleStop - angleCur <  alfaSh*0.995 && angleStop > angleCur )
                {
                    angleCur = angleStop;
                }
            }
            break; 
         }
        case 4: {// 4=spline
              //printf("EDGE spline \n");
              nurbs2d::Curve<double> crv; // Planar curve using float32
              for(const auto& cpoint : edge.controlPoints)
              {
                crv.control_points.emplace_back(rf::Point2d<double>(cpoint.at(0), cpoint.at(1)));
              }
              crv.knots  = edge.knots;
              crv.degree = edge.degree;
              if (!nurbs2d::curveIsValid(crv)) {
                    // check if degree, knots and control points are configured as per #knots == #control points + degree + 1
                    printf("Warning EDGE spline not valid \n");
                    break;
                }
                const auto [min, max] = std::minmax_element(std::begin(crv.knots), std::end(crv.knots));
                double t{*min};
                double tmax {*max}; //double(edge.nKnots)-edge.degree+2.0;
                
                //step  estimate
                const double initStep{(tmax-t)/(edge.nKnots  *1000)};
                // auto pt1 {nurbs2d::curvePoint(crv, t+initStep)};
                // auto pt2 {nurbs2d::curvePoint(crv, t+2*initStep)};
                double step{initStep};//stepInterpolation/std::hypot(pt2.x-pt1.x, pt2.y-pt1.y)*initStep}; //estimate len of line
                
                // points interpolate
                auto ptPrev {nurbs2d::curvePoint(crv, t+initStep)};
                double len{stepInterpolation+1.0}; //> порога, чтобы добавилась первая точка
                while(t<tmax)
                {
                    auto pt = nurbs2d::curvePoint(crv, t);
                    len+=std::hypot(pt.x-ptPrev.x, pt.y-ptPrev.y);
                    if(len >= stepInterpolation)
                    {
                        if(minX > pt.x)
                            minX = pt.x;
                        pointsNew.push_back(pt);
                        len=0;
                    }
                    ptPrev = pt;
                    t+=step;
                }
               break;
               } 
        default: printf("Warning EDGE unknown \n");break;
    } 
    auto& points = contours.back().PointsRef();
    points.insert(points.end(), pointsNew.begin(),pointsNew.end());
    fillEdgesInCont++;
    if(numEdgesInCont == fillEdgesInCont) //add last edges
    {
        fillContoursInHatch++;
        if(numContoursInHatch == fillContoursInHatch)
        {
            AddHatchToProfile();
        }
    }
};    
    
void AdapterDxf::AddHatchToProfile()
{
    if(contours.size()<1)
      return;
    auto minXel = std::min_element(minXcontours.begin(), minXcontours.end());
    auto indexOuterCont = std::distance(minXcontours.begin(), minXel);
    auto indexParent = profile.ContoursRef().size();

    contours.at(indexOuterCont).SetContourType(rf::ContourType::Outer);
    rf::DataUtility::ReverseIfContourWrongDirection(contours.at(indexOuterCont));
    profile.ContoursRef().push_back(contours.at(indexOuterCont));
    profile.HierarchyRef().push_back(-1);
    for(int i = 0; i < contours.size(); i++)
    {
        if(i == indexOuterCont)
            continue;
        contours.at(i).SetContourType(rf::ContourType::Inner);
        rf::DataUtility::ReverseIfContourWrongDirection(contours.at(i));
        profile.ContoursRef().push_back(contours.at(i));
        profile.HierarchyRef().push_back(indexParent);
    }
    contours.clear(); //all contours
    minXcontours.clear(); // minimal X values for all contours
}

// EOF
