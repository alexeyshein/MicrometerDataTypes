cmake_minimum_required (VERSION 3.13)

project("MicrometerDataTypes")


## TARGET
## create target and add include path
if (NOT TARGET ${PROJECT_NAME})
    #add_library(${PROJECT_NAME} INTERFACE)
	add_library(${PROJECT_NAME} STATIC)
    add_library(rf::${PROJECT_NAME} ALIAS ${PROJECT_NAME})
endif()


set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)

file(GLOB HEADERS 
    ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp
)

file(GLOB SOURCES 
    ${PROJECT_SOURCE_DIR}/src/*.cpp
    ${PROJECT_SOURCE_DIR}/src/nurbs2d/*.h
 )

source_group("Header Files" FILES ${HEADERS})
source_group("Source Files" FILES ${SOURCES})

target_sources(${PROJECT_NAME}
  PRIVATE ${HEADERS} ${SOURCES})

target_include_directories(${PROJECT_NAME} 
    PUBLIC  ${PROJECT_SOURCE_DIR}/include
    PRIVATE ${PROJECT_SOURCE_DIR}/src/nurbs2d
    #PRIVATE dxfrw
 )

 target_link_libraries(
    ${PROJECT_NAME} 
    PRIVATE Dxflib::Dxflib
    #tinynurbs::tinynurbs
 )



