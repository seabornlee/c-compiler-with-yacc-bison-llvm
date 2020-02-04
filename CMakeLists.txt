cmake_minimum_required(VERSION 3.15)
project(mycc CXX C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 14)

include_directories(include)
add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(lib/googletest)