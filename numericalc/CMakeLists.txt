cmake_minimum_required(VERSION 3.16)
project(numericalc)

set(CMAKE_CXX_STANDARD 11)

file(GLOB_RECURSE files "src/*.cpp")

add_library(numericalc STATIC ${files} src/Matrix.cpp include/numericalc/Matrix.hpp include/numericalc/decomposition/lu.hpp src/decomposition/lu.cpp include/numericalc/norm/p_norm.hpp include/numericalc/norm/max_norm.hpp src/norm/p_norm.cpp src/norm/max_norm.cpp src/Polynomial.cpp include/numericalc/Polynomial.hpp include/numericalc/eigenvector/power_method.hpp include/numericalc/fft/fft.hpp include/numericalc/gradient/steepest_descent.hpp include/numericalc/interpolation/lagrange.hpp include/numericalc/interpolation/cubic_spline.hpp include/numericalc/ode/euler.hpp src/eigenvector/power_method.cpp src/fft/fft.cpp src/gradient/steepest_descent.cpp src/gradient/conjugate.cpp include/numericalc/gradient/conjugate.hpp src/interpolation/lagrange.cpp src/interpolation/cubic_spline.cpp src/ode/euler.cpp src/integration/newton.cpp include/numericalc/integration/newton.hpp include/numericalc/root/newton.hpp src/root/root.cpp)

target_include_directories(numericalc PUBLIC include)