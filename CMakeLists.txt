cmake_minimum_required(VERSION 2.8.2)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(${CMAKE_VERSION} VERSION_LESS 2.8.2)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project(tsp_approx
        DESCRIPTION "ATSP Approximation algorithms"
        LANGUAGES CXX)     

set(HEADERS
    ${CMAKE_SOURCE_DIR}/include/file_handler.hpp
    ${CMAKE_SOURCE_DIR}/include/timer.hpp
    ${CMAKE_SOURCE_DIR}/include/adjacency_matrix.hpp)

set(SOURCES
    ${CMAKE_SOURCE_DIR}/src/main.cpp
    ${CMAKE_SOURCE_DIR}/src/file_handler.cpp
    ${CMAKE_SOURCE_DIR}/src/adjacency_matrix.cpp)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

set_target_properties(
  ${PROJECT_NAME} PROPERTIES
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED ON
  COMPILE_FLAGS "${WARNING_FLAGS}"
)