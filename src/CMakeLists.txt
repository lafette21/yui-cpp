set(EXEC_NAME example)

add_executable(${EXEC_NAME}
    main.cc
)

target_include_directories(${EXEC_NAME} SYSTEM PUBLIC
    ${CMAKE_SOURCE_DIR}/deps/imgui
)

target_link_libraries(${EXEC_NAME} PUBLIC
    ${CONAN_LIBS}
    yui
)

code_analysis(${EXEC_NAME} PRIVATE)
