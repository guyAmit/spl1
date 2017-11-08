cmake_minimum_required(VERSION 3.8)
project(spl1)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Files.cpp Files.h Commands.cpp Commands.h Environment.cpp Environment.h FileSystem.cpp FileSystem.h GlobalVariables.cpp GlobalVariables.h)
add_executable(spl1 ${SOURCE_FILES})