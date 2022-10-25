/**
 * @file AdapterDxf.h
 */

/*****************************************************************************
**  $Id: AdapterDxf.h 8865 2008-02-04 18:54:02Z andrew $
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

#ifndef AdapterDxf_H
#define AdapterDxf_H

#include <set>

#include "dl_creationadapter.h"
#include "Profile.h"

/**
 * This class takes care of the entities read from the file.
 * Usually such a class would probably store the entities.
 * this one just prints some information about them to stdout.
 *
 * @author Andrew Mustun
 */
class AdapterDxf : public DL_CreationAdapter {
public:
     AdapterDxf();
     void addHatch(const DL_HatchData&) override;
     void addHatchLoop(const DL_HatchLoopData&) override;
     void addHatchEdge(const DL_HatchEdgeData&) override;
     
     rf::Profile GetProfile(){return profile;}
private:
     //when collect all loops
     void AddHatchToProfile();
private:
    bool interpolate;//interpolate 
    double stepInterpolation;
   
    rf::Profile profile;
    int numContoursInHatch;// num contours in current hatch. File may contain multiple hatches
    int fillContoursInHatch;// filled contours in hatch
    int numEdgesInCont;// edges in next loop
    int fillEdgesInCont;//edges filled in current loop

    //
    std::vector<rf::Contour> contours; //all contours in hatch
    std::vector<double> minXcontours; // minimal X values for all contours

};

#endif
