cmake_minimum_required(VERSION 3.16)
project(numericalc)

set(CMAKE_CXX_STANDARD 11)

file(GLOB_RECURSE files "src/*.cpp")

add_executable(tests ${files})
target_link_libraries(tests PRIVATE numericalc)