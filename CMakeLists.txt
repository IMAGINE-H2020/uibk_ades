cmake_minimum_required(VERSION 3.1)
project(libades)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_BUILD_TYPE Release)
set(LIBRARY_NAME imagine-ades)

find_package(Boost REQUIRED COMPONENTS system serialization)
find_package(Armadillo)


find_path(MLPACK_INCLUDE_DIR
  NAMES core.hpp prereqs.hpp
  PATHS /usr/local/include/mlpack/ /usr/include/mlpack/
)
if(NOT MLPACK_INCLUDE_DIR)
  message(FATAL_ERROR "MLPACK_INCLUDE_DIR not found!")
endif()


find_library(MLPACK_LIBRARY
  NAMES libmlpack.so
  PATHS /usr/local/lib/
)
if(NOT MLPACK_LIBRARY)
  message(FATAL_ERROR "MLPACK_LIBRARY not found!")
endif()


include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${Boost_INCLUDE_DIR}
  ${ARMADILLO_INCLUDE_DIR}
  ${MLPACK_INCLUDE_DIR}
  GnuInstallDirs
)


file (
  GLOB_RECURSE
  SRC_FILES
  src/*
)


file (
  GLOB_RECURSE
  INCLUDE_FILES
  include/*
)

file (
  GLOB_RECURSE
  EXAMPLES_FILES
  examples/*
)


add_library (
  ${LIBRARY_NAME}
  SHARED
  ${SRC_FILES}
  ${INCLUDE_FILES}
)

target_link_libraries (
  ${LIBRARY_NAME}
  ${Boost_LIBRARIES}
  ${MLPACK_LIBRARY}
  ${ARMADILLO_LIBRARIES}
)

export(TARGETS ${LIBRARY_NAME} FILE "${PROJECT_BINARY_DIR}/ADEStargets.cmake")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})
list(APPEND CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
# Adding example subdirectory
add_subdirectory(examples)

# add a target to generate API documentation with Doxygen
find_package(Doxygen)
if(DOXYGEN_FOUND)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/adesdoc.config ${CMAKE_CURRENT_BINARY_DIR}/adesdoc_built.config @ONLY)
    add_custom_target(doc
        ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/adesdoc_built.config WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen" VERBATIM
        )
endif(DOXYGEN_FOUND)

#install(TARGETS ${LIBRARY_NAME} DESTINATION /usr/local/lib)
