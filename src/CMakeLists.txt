set(IMGUI_PATH ${CMAKE_SOURCE_DIR}/deps/imgui)

add_library(imgui-backend-GL
    ${IMGUI_PATH}/backends/imgui_impl_glfw.cpp
    ${IMGUI_PATH}/backends/imgui_impl_opengl2.cpp
)

target_include_directories(imgui-backend-GL SYSTEM PUBLIC
    ${IMGUI_PATH}
)

target_link_libraries(imgui-backend-GL
    glfw        # TODO: CMake target (create a CMake config for the dependency)
    OpenGL::GL
)

add_library(imgui
    ${IMGUI_PATH}/imgui.cpp
    ${IMGUI_PATH}/imgui_draw.cpp
    ${IMGUI_PATH}/imgui_tables.cpp
    ${IMGUI_PATH}/imgui_widgets.cpp
)

target_include_directories(imgui SYSTEM PUBLIC
    ${IMGUI_PATH}
)

set(YUI_IMPL yui)

add_library(${YUI_IMPL}
    gui.cc
)

code_analysis(${YUI_IMPL} PRIVATE)

target_include_directories(${YUI_IMPL} PUBLIC
    ${CMAKE_SOURCE_DIR}/include/yui
)

target_link_libraries(${YUI_IMPL} PUBLIC
    yui-headers
    imgui
    imgui-backend-GL
)
