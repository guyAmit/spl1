cmake_minimum_required(VERSION 3.8)
project(spl1)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES src/main.cpp src/Files.cpp include/Files.h src/Commands.cpp include/Commands.h src/Environment.cpp include/Environment.h src/FileSystem.cpp include/FileSystem.h src/GlobalVariables.cpp include/GlobalVariables.h )
add_executable(spl1 ${SOURCE_FILES})