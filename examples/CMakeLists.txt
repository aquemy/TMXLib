include_directories(${CMAKE_SOURCE_DIR}/include)

# Examples
add_executable(firstExample firstExample.cpp)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/examples)

target_link_libraries(firstExample tmx)