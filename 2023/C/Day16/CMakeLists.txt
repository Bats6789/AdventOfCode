CMAKE_MINIMUM_REQUIRED(VERSION 3.20)

# set the project name
PROJECT(AdventOfCode C)

# set the flags
set(CMAKE_CXX_FLAGS "{CMAKE_CXX_FLAGS -Wall")

# set exectuble path
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "..")

# add the executable
ADD_EXECUTABLE(Part1 Part1.c)

ADD_EXECUTABLE(Part2 Part2.c)

ADD_EXECUTABLE(Part2V2 Part2V2.c)

ADD_EXECUTABLE(Part2V3 Part2V3.c)

# Add link
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(Part2V2 PRIVATE Threads::Threads)
target_link_libraries(Part2V3 PRIVATE Threads::Threads)
