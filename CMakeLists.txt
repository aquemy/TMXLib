# TMX Library

# Minimum requiered version of cmake
cmake_minimum_required(VERSION 2.8)

# Project definition
## Name
project("TMXLibrary")

## Language
enable_language(CXX)

## Versioning
set(VERSION_MAJOR 0)
set(VERSION_MINOR 1)
set(VERSION_PATCH 0)

######################################################################################
### 2) Check dependencies
######################################################################################
 
# Dependencies
## Required
include(FindBoost)
find_package(Boost REQUIRED)

if(NOT DEFINED Boost_FOUND)
    message(FATAL_ERROR "Boost not found")
endif()

find_package(ZLIB REQUIRED)

if (NOT DEFINED ZLIB_FOUND )
    message(FATAL_ERROR "Zlib not found")
endif()


## Optional
include(FindDoxygen)
# End Dependencies

######################################################################################
### 3) Include CMake files
######################################################################################

## Configuration file for building type and flags
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/Config.cmake)

## Custom Targets file
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/Targets.cmake)

######################################################################################
### 4) Define and add paths
######################################################################################

# Sources
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src/tmx)
add_subdirectory(${SRC_DIR})

# Add examples
add_subdirectory(examples)

# Add tests
enable_testing()
add_subdirectory(test)

# Add documentation
add_subdirectory(doc)

######################################################################################
### 5) Installation
######################################################################################

install(DIRECTORY include/tmx DESTINATION include COMPONENT headers)

######################################################################################
### 6) Packaging : only in release !
######################################################################################

if("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
    include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/Package.cmake)
endif()
