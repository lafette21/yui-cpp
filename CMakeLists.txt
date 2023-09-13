cmake_minimum_required(VERSION 3.16)

# Set the project name and language
project(myproject
    VERSION 0.0.1
    DESCRIPTION ""
    HOMEPAGE_URL ""
    LANGUAGES CXX C
)

# Include cmake files
include(cmake/compiler-warnings.cmake)
include(cmake/conan-config.cmake)
include(cmake/settings.cmake)

find_package(fmt REQUIRED)
find_package(OpenGL REQUIRED)

# Setup Conan
# run_conan()

# Set project warnings
add_library(project_warnings INTERFACE)
set_project_warnings(project_warnings)

# Enable testing
enable_testing()

# Add the subdirectories
add_subdirectory(include)
add_subdirectory(src)
add_subdirectory(unit-tests)
