if(DOXYGEN_FOUND)
    set(DOC_DIR ${CMAKE_BINARY_DIR}/doc CACHE PATH "Documentation directory")
    set(DOC_CONFIG_FILE "doxyfile" CACHE PATH "Documentation configuration file")
    if(DOXYGEN_EXECUTABLE)
        add_custom_target(doc 
            COMMAND ${DOXYGEN_EXECUTABLE} ${DOC_CONFIG_FILE} 
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            )
    endif()
    configure_file("${CMAKE_SOURCE_DIR}/doc/${DOC_CONFIG_FILE}.cmake"
                   "${CMAKE_BINARY_DIR}/doc/${DOC_CONFIG_FILE}")
    install(
        DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        DESTINATION share/tmx COMPONENT doc
        PATTERN "CMakeFiles" EXCLUDE
        PATTERN "cmake_install.cmake" EXCLUDE
        PATTERN "CTestTestfile.cmake" EXCLUDE
        PATTERN "Makefile" EXCLUDE
        PATTERN "smp.cfg" EXCLUDE
        PATTERN "smp.doxytag" EXCLUDE
    )
else()
    message(STATUS "Unable to generate the documentation, Doxygen package not found")
endif()

