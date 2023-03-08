cmake_minimum_required(VERSION 3.16)
project(raytracing)
set(CMAKE_CXX_STANDARD 17)

file(GLOB SOURCE_FILES CONFIGURE_DEPENDS "src/*.h" "src/*.cc")
add_executable(raytracing ${SOURCE_FILES})