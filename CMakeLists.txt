# Project Info
cmake_minimum_required(VERSION 3.24)
set(CMAKE_CXX_STANDARD 20)

project(cpp-codebase-utils
    VERSION 0.0.1
    LANGUAGES CXX
    HOMEPAGE_URL https://github.com/jacob-thomas7/cpp-codebase-utils
)

set(UTILS_SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR})

# Check dependencies from external project
if(NOT TARGET codebase::core)
    message(FATAL_ERROR
        "Utils depends on the Core C++ Codebase."
        "\n"
        "Please add the package at: https://github.com/jacob-thomas7/cpp-codebase-core"
    )
endif()

function(create_target)
    string(TOLOWER "utils-${arg1}" TARGET_NAME)

    add_library(${TARGET_NAME} ${arg1}
        src/utils/metadata.hpp
    )

    target_include_directories(${TARGET_NAME} PUBLIC
        ${CORE_SOURCE_DIR}/include
        ${UTILS_SOURCE_DIR}/include
    )

    add_library(codebase::${TARGET_NAME} ALIAS ${TARGET_NAME})
endfunction()

# Create library
if(CORE_SHARED)
    create_target(SHARED)
endif()

if(CORE_STATIC)
    create_target(STATIC)
endif()

# Make sure codebase::utils exists, default to static if both were created
if(TARGET utils-static)
    add_library(codebase::utils ALIAS utils-static)
elseif(TARGET utils-shared)
    add_library(codebase::utils ALIAS utils-shared)
else()
    message(WARNING "codebase::utils was not created because neither UTILS_SHARED nor UTILS_STATIC were set")
endif()