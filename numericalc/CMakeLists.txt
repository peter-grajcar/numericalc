cmake_minimum_required(VERSION 3.16)
project(numericalc)

set(CMAKE_CXX_STANDARD 11)

file(GLOB_RECURSE files "src/*.cpp")

add_library(numericalc STATIC ${files})

target_include_directories(numericalc PUBLIC include)