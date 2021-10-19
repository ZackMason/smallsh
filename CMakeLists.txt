cmake_minimum_required(VERSION 2.8)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED TRUE)
set(GCC_COVERAGE_COMPILE_FLAGS "-std=c99 -g")

add_definitions(${GCC_COVERAGE_COMPILE_FLAGS})

set(PROJECT_NAME smallsh)

project(${PROJECT_NAME} C)

file(GLOB src_files
  "src/*.c"
)

add_executable(${PROJECT_NAME} ${src_files})

include_directories(include)
