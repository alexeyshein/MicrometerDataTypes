cmake_minimum_required (VERSION 3.8)

project("DxfHatchToCsvProfile")

add_executable(${PROJECT_NAME})

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)

file(GLOB_RECURSE SAMPLES_SOURCES LIST_DIRECTORIES false *.h *.hpp *.cpp)

target_sources(${PROJECT_NAME}  PRIVATE ${SAMPLES_SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE 
rf::MicrometerDataTypes
cxxopts::cxxopts

)