# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#

# TODO : Finish the cmake file to be able to compile on both linux and windows.
cmake_minimum_required (VERSION 3.8)

project ("ReseauInterurbain")

# Include sub-projects.


if(WIN32)
	find_package(wxWidgets REQUIRED)
	target_include_directory(main PRIVATE ${wxWidgets_INCLUDE_DIRS})
	target_link_libraries(main PRIVATE ${wxWidgets_LIBRARIES})
else()
	# Linux
endif()


