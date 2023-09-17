set(EXEC_NAME example)

add_executable(${EXEC_NAME}
    main.cc
)

target_link_libraries(${EXEC_NAME} PUBLIC
    yui
)

code_analysis(${EXEC_NAME} PRIVATE)
