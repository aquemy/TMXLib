include_directories(${CMAKE_SOURCE_DIR}/include)

# Examples
add_executable(firstExample firstExample.cpp)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/examples)

target_link_libraries(firstExample tmx)

execute_process(
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${CMAKE_CURRENT_SOURCE_DIR}/1.tsx
    ${CMAKE_CURRENT_BINARY_DIR}/1.tsx)
    
execute_process(
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${CMAKE_CURRENT_SOURCE_DIR}/test.tmx
    ${CMAKE_CURRENT_BINARY_DIR}/test.tmx)
