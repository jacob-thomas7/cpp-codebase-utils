# Project Info
cmake_minimum_required(VERSION 3.24)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(
    CROTALE_UTILS
    VERSION 0.1.0
    LANGUAGES CXX
)

string(TOLOWER "${PROJECT_NAME}" PROJECT_NAME_LOWER)
string(TOUPPER "${PROJECT_NAME}" PROJECT_NAME_UPPER)
string(REPLACE "crotale_" "" PROJECT_NAME_SHORT_LOWER ${PROJECT_NAME_LOWER})

# Options
set(${PROJECT_NAME}_STATIC ON CACHE BOOL "Build the utils library as a static library")
set(${PROJECT_NAME}_SHARED OFF CACHE BOOL "Build the utils library as a shared library")

# Check dependencies from external project
if(NOT TARGET crotale::core)
    message(FATAL_ERROR
        "Crotale Utils depends on Crotale Core."
        "\n"
        "Please add the package at: https://github.com/jacob-thomas7/crotale-core"
    )
endif()

function(create_target lib_type)
    string(TOLOWER "${PROJECT_NAME_LOWER}-${lib_type}" TARGET_NAME)
    string(REPLACE "crotale_" "" TARGET_NAME_SHORT ${TARGET_NAME})

    set(SRC "${${PROJECT_NAME}_SOURCE_DIR}/src/${PROJECT_NAME_SHORT_LOWER}")
    
    add_library(${TARGET_NAME} ${lib_type}
        ${SRC}/metadata.cpp
        ${SRC}/runtime.cpp
    )

    target_include_directories(${TARGET_NAME} PUBLIC
        "${${PROJECT_NAME}_SOURCE_DIR}/include/"
        "${CORE_SOURCE_DIR}/include/"
    )

    target_link_libraries(${TARGET_NAME} PUBLIC
        crotale::core
    )

    add_library(crotale::${TARGET_NAME_SHORT} ALIAS ${TARGET_NAME})
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
    add_library(crotale::${PROJECT_NAME_SHORT_LOWER} ALIAS ${PROJECT_NAME_LOWER}-static)
elseif(TARGET ${PROJECT_NAME_UPPER}-shared)
    add_library(crotale::${PROJECT_NAME_SHORT_LOWER} ALIAS ${PROJECT_NAME_LOWER}-shared)
else()
    message(WARNING "crotale::${PROJECT_NAME_SHORT_LOWER} was not created because neither ${PROJECT_NAME}_STATIC nor ${PROJECT_NAME}_SHARED were set")
endif()