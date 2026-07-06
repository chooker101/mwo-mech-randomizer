cmake_minimum_required(VERSION 3.16)
project(MWOMR CXX C)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release")

set(CMAKE_CXX_STANDARD 17)

find_package(OpenImageIO CONFIG REQUIRED)
find_package(CURL CONFIG REQUIRED)

add_subdirectory(source)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)