cmake_minimum_required(VERSION 3.16...3.25)

set(LIB_NAME engine)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/ints)
set(CMAKE_PDB_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/ints)

project(${LIB_NAME}
    VERSION 0.0.1
    LANGUAGES CXX
)

add_library(${LIB_NAME} STATIC)

add_subdirectory(src)
add_subdirectory(include)

target_include_directories(${LIB_NAME} PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/${LIB_NAME}>
    $<INSTALL_INTERFACE:include/${LIB_NAME}>
)
target_include_directories(${LIB_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

set_target_properties(${LIB_NAME} PROPERTIES
    LINK_WHAT_YOU_USE ON
    CXX_EXTENSIONS OFF
    COMPILE_FLAGS "${CMAKE_CXX_FLAGS} -fPIC"
)

if(ENABLE_PCH)
    target_precompile_headers(${LIB_NAME}
        PRIVATE <array> <string> <sstream> <vector> <iostream> <iomanip> <conio.h>
        PRIVATE <engine/core/types.hpp>
    )
endif()

target_link_libraries(${LIB_NAME}
    PRIVATE project_options project_warnings
)
