######################################################################################
### Check configuration
######################################################################################

# Inspired by Boost and SFML CMake files
if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(MACOSX 1)

    # detect OS X version. (use '/usr/bin/sw_vers -productVersion' to extract V from '10.V.x'.)
    execute_process (COMMAND /usr/bin/sw_vers -productVersion OUTPUT_VARIABLE MACOSX_VERSION_RAW)
    string(REGEX REPLACE "10\\.([0-9]).*" "\\1" MACOSX_VERSION "${MACOSX_VERSION_RAW}")
    if(${MACOSX_VERSION} LESS 5)
        message(FATAL_ERROR "Unsupported version of OS X : ${MACOSX_VERSION_RAW}")
        return()
    endif()
endif()

# Determine architecture
include(CheckTypeSize)
check_type_size(void* SIZEOF_VOID_PTR)
if("${SIZEOF_VOID_PTR}" STREQUAL "4")
    set(ARCH x86)
    set(LIB lib32)
elseif("${SIZEOF_VOID_PTR}" STREQUAL "8")
    set(ARCH x86_64)
    set(LIB lib64)
else()
    message(FATAL_ERROR "Unsupported architecture")
    return()
endif()

######################################################################################
### 0) Define general CXX flags for DEBUG and RELEASE
######################################################################################

if(DEBUG)
  set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "" FORCE)
else(DEBUG)
  set(CMAKE_BUILD_TYPE "Release" CACHE STRING "" FORCE)
endif(DEBUG)

set(CMAKE_CXX_FLAGS_DEBUG  "-Wunknown-pragmas -O0 -g -Wall -Wextra -ansi -pedantic -std=c++11 -lboost_regex -lboost_iostreams" CACHE STRING "" FORCE)
set(CMAKE_CXX_FLAGS_RELEASE  "-Wunknown-pragmas -O2 -std=c++11 -lboost_regex -lboost_iostreams" CACHE STRING "" FORCE)


######################################################################################
### 1) Define profiling flags
######################################################################################

if(PROFILING)
        set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -pg --coverage" CACHE STRING "" FORCE)
        set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "" FORCE)
        set(ENABLE_CMAKE_TESTING "true" CACHE STRING "" FORCE)
endif(PROFILING)

######################################################################################
### 3) Testing part
######################################################################################

if(ENABLE_CMAKE_TESTING)
    enable_testing()
    include(CTest REQUIRED)
endif(ENABLE_CMAKE_TESTING)

######################################################################################
### 5) Build examples ?
######################################################################################

set(ENABLE_CMAKE_EXAMPLE "true" CACHE PATH "ParadisEO examples")

