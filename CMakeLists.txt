# General

cmake_minimum_required(VERSION 3.12)

project(ft_linear_regression)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra")

# Utils library

set(SourcesDir ${CMAKE_CURRENT_SOURCE_DIR}/Sources)

file(GLOB Sources           ${SourcesDir}/Utils.hpp
                            ${SourcesDir}/Utils.cpp
)

add_library(Utils STATIC ${Sources})

# Assess executable

set(AssessDir ${CMAKE_CURRENT_SOURCE_DIR}/Assess)
file(GLOB AssessSources ${AssessDir}/main.cpp)

add_executable(Assess ${AssessSources})

target_link_libraries(Assess Utils)

target_include_directories(Assess PUBLIC ${SourcesDir})

# Learn executable

set(LearnDir ${CMAKE_CURRENT_SOURCE_DIR}/Learn)
file(GLOB AssessSources ${LearnDir}/main.cpp)

add_executable(Learn ${AssessSources})

target_link_libraries(Learn Utils)

target_include_directories(Learn PUBLIC ${SourcesDir})

# ShowPrecision executable

set(ShowPrecisionDir ${CMAKE_CURRENT_SOURCE_DIR}/ShowPrecision)
file(GLOB ShowPrecisionSources ${ShowPrecisionDir}/main.cpp)

add_executable(ShowPrecision ${ShowPrecisionSources})

target_link_libraries(ShowPrecision Utils)

target_include_directories(ShowPrecision PUBLIC ${SourcesDir})

# Visualize executable

set(VisualizeDir ${CMAKE_CURRENT_SOURCE_DIR}/Visualize)
file(GLOB VisualizeSources ${VisualizeDir}/main.cpp)

add_executable(Visualize ${VisualizeSources})

target_link_libraries(Visualize Utils)

target_include_directories(Visualize PUBLIC ${SourcesDir})

# RunUnitTests executable

set(UnitTestsDir ${CMAKE_CURRENT_SOURCE_DIR}/UnitTests)
file(GLOB UnitTestsSources      ${UnitTestsDir}/main.cpp
                                ${UnitTestsDir}/Utils.cpp
                                ${UnitTestsDir}/catch.hpp
)

add_executable(RunUnitTests ${UnitTestsSources})

target_link_libraries(RunUnitTests Utils)

target_include_directories(RunUnitTests PUBLIC ${SourcesDir})

# Definitions

add_definitions(-DPATH_TO_BUILD_DIR="${CMAKE_CURRENT_SOURCE_DIR}/Build")
add_definitions(-DPATH_TO_VISUALIZE_DIR="${CMAKE_CURRENT_SOURCE_DIR}/Visualize")
add_definitions(-DPATH_TO_ROOT_DIR="${CMAKE_CURRENT_SOURCE_DIR}")
add_definitions(-DPATH_TO_DATA_DIR="${CMAKE_CURRENT_SOURCE_DIR}/Data")
