set(LIB_NAME yui)

add_library(${LIB_NAME} INTERFACE)

target_include_directories(${LIB_NAME} INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>
    $<INSTALL_INTERFACE:include>
)

code_analysis(${LIB_NAME} INTERFACE)
