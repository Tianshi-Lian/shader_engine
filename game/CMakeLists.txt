cmake_minimum_required(VERSION 3.16...3.25)

set(APP_NAME game)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/ints)
set(CMAKE_PDB_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/ints)

project(${APP_NAME}
    VERSION 0.0.1
    LANGUAGES CXX
)

add_executable(${APP_NAME})

add_subdirectory(src)
add_subdirectory(include)

target_include_directories(${APP_NAME} PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/${APP_NAME}>
    $<INSTALL_INTERFACE:include/${APP_NAME}>
)

set_target_properties(${APP_NAME} PROPERTIES
    LINK_WHAT_YOU_USE ON
    CXX_EXTENSIONS OFF
    COMPILE_FLAGS "${CMAKE_CXX_FLAGS} -fPIC"
)

if(ENABLE_PCH)
    target_precompile_headers(${APP_NAME}
        PRIVATE <string> <sstream> <vector> <iostream>
        PRIVATE <engine/core/types.hpp> <engine/core/exception_handler.hpp>
    )
endif()

target_link_libraries(${APP_NAME}
    PRIVATE project_options project_warnings engine
)

install(
    TARGETS ${APP_NAME} DESTINATION ${CMAKE_BINARY_DIR}/dist
)
install(
    DIRECTORY ${PROJECT_SOURCE_DIR}/assets
    DESTINATION ${CMAKE_BINARY_DIR}/dist
)
