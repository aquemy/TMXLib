set(TEST_LIST firstTest)

foreach(test ${TEST_LIST})
    add_executable("${test}" "${test}.cpp")
    #target_link_libraries(${test} TMX)
    add_test(${test} ${test})
    install(TARGETS ${test} RUNTIME DESTINATION local/share/tmx/test COMPONENT tests)
endforeach(test)


