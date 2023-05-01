cmake_minimum_required(VERSION 3.16...3.25)

project(shader_engine_root)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(helpers)

set_standard_project_settings()

add_library(project_options INTERFACE)
target_compile_features(project_options INTERFACE cxx_std_17)

add_library(project_warnings INTERFACE)
set_compiler_warnings(project_warnings)

enable_static_analysis()

option(ENABLE_PCH "Enable Precompiled Headers" OFF)

# Libraries
add_subdirectory(engine)

# Applications
add_subdirectory(game)
