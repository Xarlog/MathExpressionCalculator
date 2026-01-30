cmake_minimum_required(VERSION 3.10.0)
project(MathAnalytical VERSION 0.1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
file(GLOB SOURCES "src/*.cpp")
include_directories("include")
add_library(MathAnalytical ${SOURCES})

