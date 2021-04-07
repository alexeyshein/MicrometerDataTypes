
cmake_minimum_required (VERSION 3.8)

project("DataTypesTests")

add_executable(${PROJECT_NAME})

file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false *.h *.hpp *.cpp)

target_sources(${PROJECT_NAME}  PRIVATE ${TEST_SOURCES})

add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} PUBLIC 
							rf::MicrometerDataTypes 
							)



