include_directories(${CMAKE_SOURCE_DIR}/include)

set(TMX_SRC 
    map.cpp
    tileset.cpp
    image.cpp
    layer.cpp
    imagelayer.cpp
    data.cpp
    tile.cpp
    objectgroup.cpp
    object.cpp
    properties.cpp
    polygon.cpp
    polyline.cpp
    utils.cpp
    base64/base64.cpp
    )

# Executable
add_library(tmx SHARED ${TMX_SRC})

set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

#INSTALL(TARGETS tmx ARCHIVE DESTINATION lib COMPONENT libraries)

FILE(GLOB HDRS *.h tmx)
INSTALL(FILES ${HDRS} DESTINATION include/tmx COMPONENT headers)

set_target_properties(tmx PROPERTIES VERSION 0.1)
