cmake_minimum_required(VERSION 2.8.3)
project(libades)

set (CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE Release)
set(LIBRARY_NAME libades)

find_package(mlpack)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

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
  mlpack
)

#install(TARGETS ${LIBRARY_NAME} DESTINATION /usr/lib)
