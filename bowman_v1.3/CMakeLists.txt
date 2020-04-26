cmake_minimum_required(VERSION 3.1)
project(BOWMANS)

#There are lots of scripts with cmake
#for finding external libraries. 
#see /usr/local/share/cmake-2.6/Modules/Find*.cmake for more examples
# find_package(GLUT)
# find_package(OpenGL)

set(CMAKE_CXX_FLAGS "-g -Wall")

INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
PKG_SEARCH_MODULE(SDL2TTF REQUIRED SDL2_ttf>=2.0.14)
add_subdirectory(source)
