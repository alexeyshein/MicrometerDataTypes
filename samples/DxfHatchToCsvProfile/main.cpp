#include <chrono>
#include <thread>

#include <cxxopts.hpp>
#include "ParserDxf.h"
#include "ParserCsv.h"

int main(int argc, char** argv)
{
    cxxopts::Options options("DxfHatchToCsvProfile", "Please, use options for usage ");

    options.add_options()
        ("i,input", "Input dxf file with hatch", cxxopts::value<std::string>()->default_value("input.dxf"))
        ("h,help", "Print usage");

    auto result = options.parse(argc, argv);
    if (result.count("help"))
    {
      std::cout << options.help() << std::endl;
      exit(0);
    }
     
     std::string inpFilePath = result["input"].as<std::string>();
     rf::ParserDxf parserDxf;
     rf::Profile profile;
    if(!parserDxf.Read(profile, inpFilePath))
      {
         std::cout<<"Dxf file: "<<inpFilePath<<" wasn`t parsed!"<<std::endl;
         system("pause");
         exit(0);
      }
    if(profile.ContoursConstRef().size()<1)
     {
         std::cout<<"Dxf file: "<<inpFilePath<<" didn`t contain any hatches!"<<std::endl;
         system("pause");
         exit(0);
     }
    rf::ParserCsv parserCsv;
    parserCsv.Save(profile,std::string("result.csv"));
    parserDxf.Save(profile,std::string("result.dxf"));
    system("pause");
    return 0;
}