cmake_minimum_required(VERSION 3.10)
project(eigar)
set(CMAKE_C_STANDARD 11)

include(CTest)
enable_testing()

include(build.cmake)
include(tests.cmake)