cmake_minimum_required(VERSION 3.8)
project(spl1)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES CommandsTest.cpp Include/GlobalVariables.h src/Files.cpp Include/Files.h src/Commands.cpp Include/Commands.h src/Environment.cpp Include/Environment.h src/FileSystem.cpp Include/FileSystem.h  )
add_executable(spl1 ${SOURCE_FILES})