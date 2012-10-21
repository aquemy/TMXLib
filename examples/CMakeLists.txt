include_directories(${CMAKE_SOURCE_DIR}/include)

# Examples
add_executable(firstExample firstExample.cpp)
add_executable(iterates iterates.cpp)
add_executable(simpleWrapper simpleWrapper.cpp)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/examples)

target_link_libraries(firstExample tmx)
target_link_libraries(iterates tmx)
target_link_libraries(simpleWrapper tmx)

execute_process(
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${CMAKE_CURRENT_SOURCE_DIR}/example.tsx
    ${CMAKE_CURRENT_BINARY_DIR}/example.tsx)
    
execute_process(
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${CMAKE_CURRENT_SOURCE_DIR}/example.tmx
    ${CMAKE_CURRENT_BINARY_DIR}/example.tmx)

install(TARGETS firstExample RUNTIME DESTINATION share/tmx/examples COMPONENT examples)
install(TARGETS iterates  RUNTIME DESTINATION share/tmx/examples COMPONENT examples)
install(TARGETS simpleWrapper RUNTIME DESTINATION share/tmx/examples COMPONENT examples)

install(FILES example.tmx DESTINATION share/tmx/examples COMPONENT examples)
install(FILES example.tsx DESTINATION share/tmx/examples COMPONENT examples)
    
if(SFML_EXAMPLE)
    add_subdirectory(SFML)
endif()
