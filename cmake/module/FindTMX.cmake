# File: FindTMX.cmake
# Version: 0.0.1
#
# The following variables are filled out:
# - TMX_INCLUDE_DIR : EO, MO and MOEO source dir
# - TMX_LIBRARIES :   the list of all required modules
#
# Output
# ------
#
# example:
#   find_package(TMX REQUIRED)
#   include_directories(${TMX_INCLUDE_DIR})
#   add_executable(example ...)
#   target_link_libraries(examplep ${TMX_LIBRARIES})

# enabled components
set(TMX_LIBRARIES_TO_FIND tmx)

#set the build directory
set(BUILD_DIR build)

# Path
set(TMX_SRC_PATHS
        ${TMX_ROOT}/include/
        $ENV{TMX_ROOT}
        /usr/local/
        /usr/
        /sw # Fink
        /opt/local/ # DarwinPorts
        /opt/csw/ # Blastwave
        /opt/
        [KEY_CURRENT_USER\\Software\\TMX]/local
        [HKEY_LOCAL_MACHINE\\Software\\TMX]/local
)

find_path(TMX_INCLUDE_DIR tmx
          PATHS ${TMX_SRC_PATHS})

# find the requested modules
set(TMX_FOUND true) # will be set to false if one of the required modules is not found

set(FIND_TMX_LIB_PATHS
        ${TMX_ROOT}/${BUILD_DIR}
        $ENV{TMX_ROOT}
        /usr/local/
        /usr/
        /sw # Fink
        /opt/local/ # DarwinPorts
        /opt/csw/ # Blastwave
        /opt/
        [KEY_CURRENT_USER\\Software\\TMX]/local
        [HKEY_LOCAL_MACHINE\\Software\\TMX]/local
)

#Suffixes
set(TMX_LIB_PATHS_SUFFIXES
        lib 
        lib32 
        lib64
        )
        
foreach(FIND_TMX_COMPONENT ${TMX_LIBRARIES_TO_FIND})
    string(TOUPPER ${FIND_TMX_COMPONENT} FIND_TMX_COMPONENT_UPPER)
    # release library
    find_library(TMX_${FIND_TMX_COMPONENT_UPPER}_LIBRARY
                 NAMES ${FIND_TMX_COMPONENT}
                 PATH_SUFFIXES ${TMX_LIB_PATHS_SUFFIXES}
                 PATHS ${FIND_TMX_LIB_PATHS})
    if (TMX_${FIND_TMX_COMPONENT_UPPER}_LIBRARY)
        # library found
        set(TMX_${FIND_TMX_COMPONENT_UPPER}_FOUND true)
    else()
        # library not found
        set(TMX_FOUND false)
        set(TMX_${FIND_TMX_COMPONENT_UPPER}_FOUND false)
        set(FIND_TMX_MISSING "${FIND_TMX_MISSING} ${FIND_TMX_COMPONENT}")
    endif()
    set(TMX_LIBRARIES ${TMX_LIBRARIES} "${TMX_${FIND_TMX_COMPONENT_UPPER}_LIBRARY}")
endforeach()

# handle result
if(TMX_FOUND)
    message(STATUS "Found TMX includes :")
    message(${TMX_INCLUDE_DIR})
else()
    # include directory or library not found
    message(FATAL_ERROR "Could NOT find TMX (missing : ${FIND_TMX_MISSING})")
endif()
