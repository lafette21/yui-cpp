set(YUI_HEADERS yui-headers)
set(NOVA_PATH ${CMAKE_SOURCE_DIR}/deps/nova-cpp)

add_library(${YUI_HEADERS} INTERFACE)

target_compile_definitions(${YUI_HEADERS} INTERFACE
    FMT_SYSTEM_HEADERS=ON
)

target_include_directories(${YUI_HEADERS} INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>
    $<INSTALL_INTERFACE:include>
    ${NOVA_PATH}/include
)

target_link_libraries(${YUI_HEADERS} INTERFACE
    fmt::fmt-header-only
)

code_analysis(${YUI_HEADERS} INTERFACE)
