set(YUI_HEADERS yui-headers)

add_library(${YUI_HEADERS} INTERFACE)

target_include_directories(${YUI_HEADERS} INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(${YUI_HEADERS} INTERFACE
    fmt::fmt-header-only
)

code_analysis(${YUI_HEADERS} INTERFACE)
