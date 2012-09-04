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
######################################################################################
### 1) Set paths
######################################################################################
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

add_library(tmx STATIC ${TMX_SRC})

install(TARGETS tmx ARCHIVE DESTINATION local/${LIB} COMPONENT libraries)
