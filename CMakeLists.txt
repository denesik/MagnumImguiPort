cmake_minimum_required(VERSION 2.8)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/modules/")

find_package(SDL2 REQUIRED)
find_package(Magnum REQUIRED
  Shaders
  Sdl2Application)


include_directories(${SDL2_INCLUDE_DIR})

add_subdirectory(src)

