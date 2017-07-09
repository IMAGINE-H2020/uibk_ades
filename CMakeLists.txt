cmake_minimum_required(VERSION 3.1)
project(libades)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_BUILD_TYPE Release)
set(LIBRARY_NAME libades)

find_package(Boost REQUIRED COMPONENTS system serialization)
find_package(Armadillo)


find_path(MLPACK_INCLUDE_DIR
  NAMES core.hpp prereqs.hpp
  PATHS /usr/local/include/mlpack/
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

#install(TARGETS ${LIBRARY_NAME} DESTINATION /usr/local/lib)
