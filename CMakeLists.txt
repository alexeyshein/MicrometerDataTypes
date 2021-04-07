cmake_minimum_required (VERSION 3.13)

project("MicrometerDataTypesSolution")


# Optional  components
# ===================================================
option(WITH_MicrometerDataTypes_Tests  "Include Unit Tests" ON)

#add_subdirectory (3rdParty)
add_subdirectory (lib)

if(WITH_MicrometerDataTypes_Tests)
	add_definitions(-DBUILD_Test)
	add_subdirectory (tests)
endif()




