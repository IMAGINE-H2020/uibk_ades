cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
project(libades LANGUAGES CXX)


# Some properties
set(LIBADES_MAJOR_VERSION 0)
set(LIBADES_MINOR_VERSION 1)
set(LIBADES_PATCH_VERSION 0)
set(LIBADES_VERSION ${LIBADES_MAJOR_VERSION}.${LIBADES_MINOR_VERSION}.${LIBADES_PATCH_VERSION})
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE Debug)
set(LIBRARY_NAME libades)


# Offer the user the choice of overriding the installation directories
set(INSTALL_LIB_DIR lib CACHE PATH "Installation directory for libraries")
set(INSTALL_BIN_DIR bin CACHE PATH "Installation directory for executables")
set(INSTALL_INCLUDE_DIR include CACHE PATH "Installation directory for header files")
set(DEF_INSTALL_CMAKE_DIR lib/cmake/${LIBRARY_NAME}/)
set(INSTALL_CMAKE_DIR ${DEF_INSTALL_CMAKE_DIR} CACHE PATH
  "Installation directory for CMake files")
# Make relative paths absolute (needed later on)
foreach(p LIB BIN INCLUDE CMAKE)
  set(var INSTALL_${p}_DIR)
  if(NOT IS_ABSOLUTE "${${var}}")
    set(${var} "${CMAKE_INSTALL_PREFIX}/${${var}}")
  endif()
endforeach()


# IMPORTED TARGETS

include(GNUInstallDirs)

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
add_subdirectory(src/examples EXCLUDE_FROM_ALL)


# Add all targets to the build-tree export set
export(TARGETS libades populating_ades populating_db save_load_ades
	FILE "${PROJECT_BINARY_DIR}/LibADESTargets.cmake")
 
# Export the package for use from the build-tree
# (this registers the build-tree with a global CMake-registry)
export(PACKAGE libades)
 
# Create the LibADESConfig.cmake and LibADESConfigVersion files
file(RELATIVE_PATH REL_INCLUDE_DIR "${INSTALL_CMAKE_DIR}"
   "${INSTALL_INCLUDE_DIR}")
# ... for the build tree
set(CONF_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}" "${PROJECT_BINARY_DIR}")
configure_file(LibADESConfig.cmake.in
	"${PROJECT_BINARY_DIR}/LibAdesConfig.cmake" @ONLY)
# ... for the install tree
set(CONF_INCLUDE_DIRS "\${LIBADES_CMAKE_DIR}/${REL_INCLUDE_DIR}")
configure_file(LibADESConfig.cmake.in
  "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/LibADESConfig.cmake" @ONLY)
# ... for both
configure_file(LibADESConfigVersion.cmake.in
  "${PROJECT_BINARY_DIR}/LibADESConfigVersion.cmake" @ONLY)
 
# Install the LibADESConfig.cmake and LibADESConfigVersion.cmake
install(FILES
  "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/LibADESConfig.cmake"
  "${PROJECT_BINARY_DIR}/LibADESConfigVersion.cmake"
  DESTINATION "${INSTALL_CMAKE_DIR}" COMPONENT dev)
 
# Install the export set for use with the install-tree
install(EXPORT LibADESTargets DESTINATION
  "${INSTALL_CMAKE_DIR}" COMPONENT dev)


# Documentation
# first we can indicate the documentation build as an option and set it to ON by default
option(BUILD_DOC "Build documentation" OFF)

# check if Doxygen is installed
find_package(Doxygen)
if (DOXYGEN_FOUND)
    # set input and output files
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    # request to configure the file
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    message("Doxygen build started")

    # note the option ALL which allows to build the docs together with the application
    add_custom_target( doc ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen."
        VERBATIM )
else (DOXYGEN_FOUND)
  message("Doxygen must to be installed to generate documentation.")
endif (DOXYGEN_FOUND)


# Eigen info
message(STATUS "Depending on your eigen installation, you may have to create symbolic links for that Eigen/Dense are found at runtime :
    cd <your/path/to/eigen>
    sudo ln -sf eigen3/Eigen Eigen
    sudo ln -sf eigen3/unsupported unsupported")
