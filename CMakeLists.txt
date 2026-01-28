cmake_minimum_required(VERSION 3.10.0)
project(MathAnalytical VERSION 0.1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(SOURCES Const.cpp Var.cpp Negative.cpp Addition.cpp Subtraction.cpp Multiplication.cpp Exp.cpp Division.cpp NatLog.cpp Pow.cpp Cosine.cpp Sine.cpp Tangent.cpp ArcSine.cpp ArcCosine.cpp ArcTangent.cpp)
add_library(MathAnalytical ${SOURCES})

