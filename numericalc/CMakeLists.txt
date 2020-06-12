cmake_minimum_required(VERSION 3.16)
project(numericalc)

set(CMAKE_CXX_STANDARD 11)

file(GLOB_RECURSE files "src/*.cpp")

add_library(numericalc STATIC ${files} src/Matrix.cpp include/numericalc/Matrix.hpp include/numericalc/decomposition/lu.hpp src/decomposition/lu.cpp include/numericalc/norm/p_norm.hpp include/numericalc/norm/max_norm.hpp src/norm/p_norm.cpp src/norm/max_norm.cpp)

target_include_directories(numericalc PUBLIC include)