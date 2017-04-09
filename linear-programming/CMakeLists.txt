cmake_minimum_required (VERSION 2.8)

project(demo)

set(CMAKE_CXX_STANDARD 11)
set(EXECUTABLE_OUTPUT_PATH ..)
set(CMAKE_CXX_FLAGS -g)
# set(CMAKE_CXX_FLAGS -Wwrite-strings)

aux_source_directory(./src DIR_SRCS)
#add_executable(demo src/main.cpp ${DIR_SRCS})
add_executable(demo src/test.cpp ${DIR_SRCS})

#add_executable(test test/main.cpp ${DIR_SRCS})
