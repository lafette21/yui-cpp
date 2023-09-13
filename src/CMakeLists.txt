set(IMGUI_PATH ${CMAKE_SOURCE_DIR}/deps/imgui)

add_library(imgui-backend-GL SHARED
    ${IMGUI_PATH}/backends/imgui_impl_glfw.cpp
    ${IMGUI_PATH}/backends/imgui_impl_opengl2.cpp
)

target_include_directories(imgui-backend-GL SYSTEM PUBLIC
    ${IMGUI_PATH}
)

target_link_libraries(imgui-backend-GL
    glfw
    OpenGL::GL
)

add_library(imgui SHARED
    ${IMGUI_PATH}/imgui.cpp
    ${IMGUI_PATH}/imgui_draw.cpp
    ${IMGUI_PATH}/imgui_tables.cpp
    ${IMGUI_PATH}/imgui_widgets.cpp
)

target_include_directories(imgui SYSTEM PUBLIC
    ${IMGUI_PATH}
)

set(LIB_NAME yui)

add_library(${LIB_NAME} SHARED
    gui.cc
)

code_analysis(${LIB_NAME} PRIVATE)

target_include_directories(${LIB_NAME} PUBLIC
    ${CMAKE_SOURCE_DIR}/include/yui
)

target_link_libraries(${LIB_NAME} PUBLIC
    imgui
    imgui-backend-GL
)

set(EXEC_NAME example)

add_executable(${EXEC_NAME}
    main.cc
)

target_link_libraries(${EXEC_NAME} PUBLIC
    fmt::fmt-header-only
    yui
    yui-devel
)

code_analysis(${EXEC_NAME} PRIVATE)
