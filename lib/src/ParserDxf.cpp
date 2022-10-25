#include "ParserDxf.h"
#include <filesystem>
#include <string>
#include <dl_dxf.h>//dxflib
#include <set>
#include "AdapterDxf.h"

using namespace rf;
namespace fs = std::filesystem;

ParserDxf::ParserDxf() : delimeter{";"}
{
}

ParserDxf::~ParserDxf()
{
}

void WriteHeader( DL_Dxf& dxf, DL_WriterA* dw)
{
     // section header:
    dxf.writeHeader(*dw);
    dw->sectionEnd();
 
    // section tables:
    dw->sectionTables();

    // VPORT:
    dxf.writeVPort(*dw);

    // LTYPE:
    dw->tableLinetypes(1);
    dxf.writeLinetype(*dw, DL_LinetypeData("CONTINUOUS", "Continuous", 0, 0, 0.0));
    dxf.writeLinetype(*dw, DL_LinetypeData("BYLAYER", "", 0, 0, 0.0));
    dxf.writeLinetype(*dw, DL_LinetypeData("BYBLOCK", "", 0, 0, 0.0));
    dw->tableEnd();

    // LAYER:
    dw->tableLayers(1);
    dxf.writeLayer(
        *dw,
        DL_LayerData("0", 0),
        DL_Attributes("", 2, 0, 0, "CONTINUOUS")
    );
    dw->tableEnd();

    // STYLE:
    dw->tableStyle(1);
    // name,flags,fixedTextHeight,  widthFactor, obliqueAngle, textGenerationFlags,  lastHeightUsed,  primaryFontFile, bigFontFile
    DL_StyleData style("Standard", 0, 0.0, 3.0, 0.0, 0, 2.5, "txt", "");

    style.bold = false;
    style.italic = false;
    dxf.writeStyle(*dw, style);
    dw->tableEnd();

    // VIEW:
    dxf.writeView(*dw);

    // UCS:
    dxf.writeUcs(*dw);

    // APPID:
    dw->tableAppid(1);
    dxf.writeAppid(*dw, "ACAD");
    dw->tableEnd();

    // DIMSTYLE:
    dxf.writeDimStyle(*dw, 1, 1, 1, 1, 30);

    // BLOCK_RECORD:
    dxf.writeBlockRecord(*dw);
    dw->tableEnd();

    dw->sectionEnd();
 
    // BLOCK:
    dw->sectionBlocks();
    dxf.writeBlock(*dw, DL_BlockData("*Model_Space", 0, 0.0, 0.0, 0.0));
    dxf.writeEndBlock(*dw, "*Model_Space");
    dxf.writeBlock(*dw, DL_BlockData("*Paper_Space", 0, 0.0, 0.0, 0.0));
    dxf.writeEndBlock(*dw, "*Paper_Space");
    dxf.writeBlock(*dw, DL_BlockData("*Paper_Space0", 0, 0.0, 0.0, 0.0));
    dxf.writeEndBlock(*dw, "*Paper_Space0");
    dw->sectionEnd();
}

void WriteHatchLoop(DL_Dxf& dxf, DL_WriterA* dw, const Contour &contour)
{
      const auto pointsRef = contour.PointsConstRef();
      const auto pointsCount = pointsRef.size();
      if(pointsCount<3)
        return;
      DL_HatchLoopData lData(pointsCount);
      dxf.writeHatchLoop1(*dw, lData);

      // write edges:
      for(int i=1;i<pointsCount;i++)
      {
         const auto& p1 = pointsRef.at(i-1);
         const auto& p2 = pointsRef.at(i);
         dxf.writeHatchEdge(*dw, DL_HatchEdgeData(p1.x,p1.y,p2.x,p2.y));
      }
      //Замыкаем последнюю на первую точки
      const auto& p1 = pointsRef.at(pointsCount-1);
      const auto& p2 = pointsRef.at(0);
      dxf.writeHatchEdge(*dw, DL_HatchEdgeData(p1.x,p1.y,p2.x,p2.y));

      // end loop:
      dxf.writeHatchLoop2(*dw, lData);
}

bool ParserDxf::Save(const Profile& profile, const std::string &pathStr)
{
   const auto &contoursVec = profile.ContoursConstRef();
   const auto &hierarchyVec = profile.HierarchyConstRef();

   std::fstream myFile;
   fs::path path(pathStr);
   fs::path parentPath = path.parent_path();

  if(!parentPath.empty()) 
   {
      if (!fs::exists(parentPath))
      {
         fs::create_directories(parentPath);
      }
   }
    DL_Dxf dxf;
    std::unique_ptr<DL_WriterA> dw {dxf.out(pathStr.c_str(), DL_Codes::AC1015)};
   
   WriteHeader(dxf, dw.get());

    // ENTITIES:
    dw->sectionEntities();
    DL_Attributes attributes("0", 2, 0, -1, "BYLAYER");

    for(int c=0; c < contoursVec.size(); c++)
    {
       if(contoursVec.at(c).GetContourType() == rf::ContourType::Outer())
       {
            int countChildren = std::count_if(hierarchyVec.begin(), hierarchyVec.end(), [&,c](const auto& h){return h == c;});
            // start hatch with two loops:
            DL_HatchData data(countChildren+1, true, 10.0, 0.0, "ESCHER", 0.0, 0.0);
            dxf.writeHatch1(*dw, data, attributes);
            WriteHatchLoop(dxf, dw.get(), contoursVec.at(c)); //Записываем внешний контур
            for(int h=0; h < hierarchyVec.size(); h++)
            {
               if(hierarchyVec.at(h) == c)
                  WriteHatchLoop(dxf, dw.get(), contoursVec.at(h)); //Записываем внутренний контур
            }
            // end hatch:
            dxf.writeHatch2(*dw, data, attributes);
       }
    }

    // end section ENTITIES:
    dw->sectionEnd();
    dxf.writeObjects(*dw, "MY_OBJECTS");
    dxf.writeObjectsEnd(*dw);
 
    dw->dxfEOF();
    dw->close();
   return true;
}

bool ParserDxf::Read(Profile& profile, const std::string &path)
{
   auto& contours = profile.ContoursRef();
   auto& hierarchy =  profile.HierarchyRef();
   contours.clear();
   hierarchy.clear();
   
       // Load DXF file into memory:
    std::unique_ptr<AdapterDxf> creationClass {new AdapterDxf()};
    std::unique_ptr<DL_Dxf> dxf {new DL_Dxf()};
    if (!dxf->in(path.c_str(), creationClass.get())) { // if file open failed
        std::cerr << path << " could not be opened.\n";
        profile = Profile();
        return false;
    }
    profile = creationClass->GetProfile();
   return true;
}


bool ParserDxf::Save(const Contour& contour, const std::string &pathStr)
{
   return true;
}


bool ParserDxf::Read(Contour& contour, const std::string &path)
{
   return true;
}