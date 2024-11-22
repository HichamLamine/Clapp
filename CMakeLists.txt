cmake_minimum_required(VERSION 3.16)

project(Clapp VERSION 1.0 LANGUAGES C)

include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB_RECURSE SOURCE_FILES
    "${PROJECT_SOURCE_DIR}/src/*.c"
)

add_executable(clapp ${SOURCE_FILES})

