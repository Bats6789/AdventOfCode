CMAKE_MINIMUM_REQUIRED(VERSION 3.20)

# set the project name
PROJECT(AdventOfCode C)

# set the flags
set(CMAKE_CXX_FLAGS "{CMAKE_CXX_FLAGS -Wall")

# set exectuble path
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "..")

# add the executable
ADD_EXECUTABLE(Part1 Part1.c)
target_link_libraries(Part1 m)

ADD_EXECUTABLE(Part2 Part2.c)
target_link_libraries(Part2 m)
