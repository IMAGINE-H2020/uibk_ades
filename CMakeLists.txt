cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
project(libades VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE Debug)
set(LIBRARY_NAME imagine-ades)

include(GNUInstallDirs)

# IMPORTED TARGETS

# Boost
find_package(Boost REQUIRED COMPONENTS system serialization filesystem)
add_library(boost INTERFACE IMPORTED)
set_property(TARGET boost PROPERTY
	INTERFACE_INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR})
set_property(TARGET boost PROPERTY
	INTERFACE_LINK_LIBRARIES ${Boost_LIBRARIES})

# Armadillo
find_package(Armadillo)
add_library(armadillo INTERFACE IMPORTED)
set_property(TARGET armadillo PROPERTY
	INTERFACE_INCLUDE_DIRECTORIES ${ARMADILLO_INCLUDE_DIR})
set_property(TARGET armadillo PROPERTY
	INTERFACE_LINK_LIBRARIES ${ARMADILLO_LIBRARIES})

#MLPack
find_path(MLPack_INCLUDE_DIR
  NAMES core.hpp prereqs.hpp
  PATHS /usr/local/include/mlpack/ /usr/include/mlpack/
)
if(NOT MLPack_INCLUDE_DIR)
  message(FATAL_ERROR "MLPack_INCLUDE_DIR not found!")
endif()
find_library(MLPack_LIBRARIES
  NAMES libmlpack.so
  PATHS /usr/local/lib/
)
if(NOT MLPack_LIBRARIES)
  message(FATAL_ERROR "MLPack_LIBRARIES not found!")
endif()
add_library(mlpack INTERFACE IMPORTED)
set_property(TARGET mlpack PROPERTY
	INTERFACE_INCLUDE_DIRECTORIES ${MLPackINCLUDE_DIR})
set_property(TARGET mlpack PROPERTY
	INTERFACE_LINK_LIBRARIES ${MLPack_LIBRARIES})

#LibGP
find_path(LibGP_INCLUDE_DIR
  NAMES gp.h
  PATHS /usr/local/include/gp/
)
if(NOT LibGP_INCLUDE_DIR)
	message(FATAL_ERROR "LibGP_INCLUDE_DIR not found!")
endif()
find_library(LibGP_LIBRARIES
  NAMES libgp.a
  PATHS /usr/local/lib/
)
if(NOT LibGP_LIBRARIES)
	message(FATAL_ERROR "LibGP_LIBRARIES not found!")
endif()
add_library(libgp INTERFACE IMPORTED)
set_property(TARGET libgp PROPERTY
	INTERFACE_INCLUDE_DIRECTORIES ${LibGP_INCLUDE_DIR})
set_property(TARGET libgp PROPERTY
	INTERFACE_LINK_LIBRARIES ${LibGP_LIBRARIES})


# TARGETS
add_subdirectory(src/libades)
add_subdirectory(src/examples)


# Documentation
find_package(Doxygen)
if(DOXYGEN_FOUND)
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/doc.config ${CMAKE_CURRENT_BINARY_DIR}/doc_built.config @ONLY)
    add_custom_target(doc
        ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/doc_built.config WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen" VERBATIM
        )
endif(DOXYGEN_FOUND)

message(STATUS "Depending on your eigen installation, you may have to create symbolic links for that Eigen/Dense are found at runtime :
    cd <your/path/to/eigen>
    sudo ln -sf eigen3/Eigen Eigen
    sudo ln -sf eigen3/unsupported unsupported")
