# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#

# TODO : Finish the cmake file to be able to compile on both linux and windows.
cmake_minimum_required (VERSION 3.20)

project (ReseauInterurbain VERSION 1.0)

set(wxWidgets_ROOT_DIR ${WXDIR})
set(wxWidgets_LIB_DIR ${WXLIB})
set(wxWidgets_wxrc_EXECUTABLE "${WXLIB}/wxrc.exe")
SET(wxWidgets_CONFIGURATION mswud)
set(wxWidgets_EXCLUDE_COMMON_LIBRARIES FALSE)

find_package(wxWidgets 3.1 REQUIRED)
include(${wxWidgets_USE_FILE})

add_subdirectory(src)

