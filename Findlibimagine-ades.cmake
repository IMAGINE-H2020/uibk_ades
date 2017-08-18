# - Try to find Libimagine-ades
# Once done this will define
#  LIBIMAGINE-ADES_FOUND - System has Libimagine-ades
#  LIBIMAGINE-ADES_INCLUDE_DIRS - The Libimagine-ades include directories
#  LIBIMAGINE-ADES_LIBRARIES - The libraries needed to use Libimagine-ades
#  LIBIMAGINE-ADES_DEFINITIONS - Compiler switches required for using Libimagine-ades

find_package(PkgConfig)
pkg_check_modules(PC_LIBIMAGINE-ADES QUIET libimagine-ades)
set(LIBIMAGINE-ADES_DEFINITIONS ${PC_LIBIMAGINE-ADES_CFLAGS_OTHER})

find_path(LIBIMAGINE-ADES_INCLUDE_DIR libxml/xpath.h
    HINTS ${PC_LIBIMAGINE-ADES_INCLUDEDIR} ${PC_LIBIMAGINE-ADES_INCLUDE_DIRS}
    PATH_SUFFIXES libimagine-ades)

find_library(LIBIMAGINE-ADES_LIBRARY NAMES imagine-ades libimagine-ades
    HINTS ${PC_LIBIMAGINE-ADES_LIBDIR} ${PC_LIBIMAGINE-ADES_LIBRARY_DIRS} )

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set LIBIMAGINE-ADES_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(LibXml2  DEFAULT_MSG
    LIBIMAGINE-ADES_LIBRARY LIBIMAGINE-ADES_INCLUDE_DIR)

mark_as_advanced(LIBIMAGINE-ADES_INCLUDE_DIR LIBIMAGINE-ADES_LIBRARY )

set(LIBIMAGINE-ADES_LIBRARIES ${LIBIMAGINE-ADES_LIBRARY} )
set(LIBIMAGINE-ADES_INCLUDE_DIRS ${LIBIMAGINE-ADES_INCLUDE_DIR} )

