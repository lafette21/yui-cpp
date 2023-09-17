set(EXEC_NAME test-example)

add_executable(${EXEC_NAME}
    sample.cc
)

find_package(GTest REQUIRED)

target_link_libraries(${EXEC_NAME} PRIVATE
    GTest::gtest
    GTest::gtest_main
)

code_analysis(${EXEC_NAME} PRIVATE)

add_test(${EXEC_NAME} ${EXEC_NAME})
