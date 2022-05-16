 # Sets the minimum required version of cmake for a project.
cmake_minimum_required(VERSION 3.9.1)


# Sets the project name and version.
project(Sudoku VERSION 1.0)


# Specify the C++ standard.
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)


# Setting Wall flag for compiler ( "warn all" ).
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")


# Setting the path for the exec file (creates bin folder).
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)


# Creating a variable named ${SOURCES} (could be as a list (paths separated by a space)) to include target sources.
set(SOURCES ${PROJECT_SOURCE_DIR}/src/main.cpp)


# Adds an executable to the project using the specified source files
add_executable(sudoku ${SOURCES})

