cmake_minimum_required (VERSION 3.0.2)
set(MY_PROJECT_NAME "program")
set(CMAKE_CXX_FLAGS "${CMAKE_CSS_FLAGS} -std=c++11 -Wall -pedantic")

project(MY_PROJECT_NAME)

#Bring the headers into the project
include_directories(include)
 
#The file(GLOB...) allows for wildcard additions:
file(GLOB SOURCES "src/*.cpp")
 
add_executable(${MY_PROJECT_NAME} ${SOURCES})

