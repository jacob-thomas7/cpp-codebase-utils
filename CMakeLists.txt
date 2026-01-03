# Project Info
cmake_minimum_required(VERSION 3.24)
set(CMAKE_CXX_STANDARD 20)

project(UTILS
    VERSION 0.0.2
    LANGUAGES CXX
    HOMEPAGE_URL https://github.com/jacob-thomas7/cpp-codebase-utils
)

string(TOLOWER "${PROJECT_NAME}" PROJECT_NAME_LOWER)

# Options
set(${PROJECT_NAME}_STATIC ON CACHE BOOL "Build the utils library as a static library")
set(${PROJECT_NAME}_SHARED OFF CACHE BOOL "Build the utils library as a shared library")

# Check dependencies from external project
if(NOT TARGET codebase::core)
    message(FATAL_ERROR
        "Utils depends on the Core C++ Codebase."
        "\n"
        "Please add the package at: https://github.com/jacob-thomas7/cpp-codebase-core"
    )
endif()

function(create_target lib_type)
    string(TOLOWER "${PROJECT_NAME_LOWER}-${lib_type}" TARGET_NAME)

    set(SRC "${UTILS_SOURCE_DIR}/src/${PROJECT_NAME_LOWER}")
    
    add_library(${TARGET_NAME} ${lib_type}
        ${SRC}/metadata.cpp
    )

    target_include_directories(${TARGET_NAME} PUBLIC
        "${${PROJECT_NAME}_SOURCE_DIR}/include/"
        "${CORE_SOURCE_DIR}/include/"
    )

    add_library(codebase::${TARGET_NAME} ALIAS ${TARGET_NAME})
endfunction()

# Create library
if(${PROJECT_NAME}_SHARED)
    create_target(SHARED)
endif()

if(${PROJECT_NAME}_STATIC)
    create_target(STATIC)
endif()

# Make sure the default target exists, default to static if both were created
if(TARGET ${PROJECT_NAME_LOWER}-static)
    add_library(codebase::${PROJECT_NAME_LOWER} ALIAS ${PROJECT_NAME_LOWER}-static)
elseif(TARGET ${PROJECT_NAME_UPPER}-shared)
    add_library(codebase::${PROJECT_NAME_LOWER} ALIAS ${PROJECT_NAME_LOWER}-shared)
else()
    message(WARNING "codebase::${PROJECT_NAME_LOWER} was not created because neither ${PROJECT_NAME}_STATIC nor ${PROJECT_NAME}_SHARED were set")
endif()