
project(perlinNoise)

cmake_minimum_required(VERSION 3.7)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

set(GCC_COVERAGE_COMPILE_FLAGS "-std=c++11 -Wall")
#Append the project flags to the cmake variable flag
add_definitions(${GCC_COVERAGE_COMPILE_FLAGS})
#set(CMAKE_CSS_FLAGS "${CMAKE_CSS_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")

add_subdirectory("src")

add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} src)
