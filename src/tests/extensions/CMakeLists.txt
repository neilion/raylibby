cmake_minimum_required(VERSION 3.25)
project(extensionTests)

set(CMAKE_CXX_STANDARD 23)

# Test executables for extensions
# Requires the raylib header

set(SOURCES_DIR "${CMAKE_SOURCE_DIR}/src")

file(GLOB EXTENSIONS_SOURCES
        "${SOURCES_DIR}/extensions/*.cpp")

set(SOURCES_INCLUDE_DIRS
        "${SOURCES_DIR}/extensions/")

# Create vector3 extensions test executable
add_executable(testExtensions)
target_sources(testExtensions
        PRIVATE
        "${EXTENSIONS_SOURCES}"
        "testExtensionsMain.cpp")
target_include_directories(testExtensions
        PRIVATE
        "${SOURCES_INCLUDE_DIRS}"
        )
target_link_libraries(testExtensions
        PRIVATE
        raylib
        )
