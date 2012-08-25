set(TEST_LIST firstTest)

foreach(test ${TEST_LIST})
    add_executable("${test}" "${test}.cpp")
    #target_link_libraries(${test} TMX)
    add_test(${test} ${test})
endforeach(test)

add_test(firstTest ${CMAKE_CURRENT_BINARY_DIR}/firstTest firstTest)
