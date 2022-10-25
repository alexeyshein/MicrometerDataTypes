cmake_minimum_required (VERSION 3.13)

project("MicrometerDataTypesSolution")


# Optional  components
# ===================================================
option(WITH_MicrometerDataTypes_Tests  "Include Unit Tests" ON)
option(WITH_MicrometerDataTypes_Samples "Include Samples" OFF)


add_subdirectory (3rdParty)
add_subdirectory (lib)

if(WITH_MicrometerDataTypes_Tests)
	add_definitions(-DBUILD_Test)
	add_subdirectory (tests)
endif()


# Включите подпроекты.
if(WITH_MicrometerDataTypes_Samples)
	add_definitions(-DBUILD_Samples)
	add_subdirectory (samples)
endif()

