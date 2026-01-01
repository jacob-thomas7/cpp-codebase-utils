# Project Info
cmake_minimum_required(VERSION 3.24)
set(CMAKE_CXX_STANDARD 20)

project(UTILS
    VERSION 0.0.4
    LANGUAGES CXX
    HOMEPAGE_URL https://github.com/jacob-thomas7/cpp-codebase-utils
)

# Options
set(UTILS_STATIC ON CACHE BOOL "Build the utils library as a static library")
set(UTILS_SHARED OFF CACHE BOOL "Build the utils library as a shared library")

# Check dependencies from external project
if(NOT TARGET codebase::core)
    message(FATAL_ERROR
        "Utils depends on the Core C++ Codebase."
        "\n"
        "Please add the package at: https://github.com/jacob-thomas7/cpp-codebase-core"
    )
endif()

function(create_target lib_type)
    string(TOLOWER "${PROJECT_NAME}-${lib_type}" TARGET_NAME)

    set(SRC "${UTILS_SOURCE_DIR}/src/utils")

    add_library(${TARGET_NAME} ${lib_type}
        ${SRC}/metadata.cpp
    )

    target_include_directories(${TARGET_NAME} PUBLIC
        ${UTILS_SOURCE_DIR}/include
    )

    add_library(codebase::${TARGET_NAME} ALIAS ${TARGET_NAME})
endfunction()

# Create library
if(UTILS_SHARED)
    create_target(SHARED)
endif()

if(UTILS_STATIC)
    create_target(STATIC)
endif()

# Make sure codebase::core exists, default to static if both were created
if(TARGET ${PROJECT_NAME}-static)
    add_library(codebase::${PROJECT_NAME} ALIAS ${PROJECT_NAME}-static)
elseif(TARGET core-shared)
    add_library(codebase::${PROJECT_NAME} ALIAS ${PROJECT_NAME}-shared)
else()
    message(WARNING "codebase::${PROJECT_NAME} was not created because neither UTILS_SHARED nor UTILS_STATIC were set")
endif()