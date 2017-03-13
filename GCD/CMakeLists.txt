cmake_minimum_required (VERSION 2.8.12)
project (gcd_benchmark)

SET(CMAKE_CXX_FLAGS -std=c++11)
#SET(CMAKE_CXX_FLAGS --benchmark_format=<console>)

ADD_EXECUTABLE(main greatest-common-divisor.cpp)

target_link_libraries(main benchmark)
target_link_libraries(main pthread)
