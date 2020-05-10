cmake_minimum_required(VERSION 3.7)

project(ezcommon)

add_library(ezcommon INTERFACE)

target_sources(ezcommon INTERFACE ${EZCOMMON_H_FILES} ${EZCOMMON_TCC_FILES})
target_include_directories(ezcommon INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/include/")