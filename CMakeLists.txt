# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#

# TODO : Finish the cmake file to be able to compile on both linux and windows.
cmake_minimum_required (VERSION 3.20)

project (ReseauInterurbain VERSION 1.0)

add_subdirectory(src)

if(BUILD_TESTING)
	include (FetchContent)

	FetchContent_Declare(
		googletest
		GIT_REPOSITORY https://github.com/google/googletest.git
		GIT_TAG        e2239ee6043f73722e7aa812a459f54a28552929 # release-1.11.0
	)

	if (WIN32)
		set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
	endif()

	FetchContent_MakeAvailable(googletest)
	enable_testing ()

	add_subdirectory(test)
else()
	set(wxWidgets_ROOT_DIR ${WXDIR})
	set(wxWidgets_LIB_DIR ${WXLIB})
	set(wxWidgets_wxrc_EXECUTABLE "${WXLIB}/wxrc.exe")
	set(wxWidgets_CONFIGURATION mswud)
	set(wxWidgets_EXCLUDE_COMMON_LIBRARIES FALSE)
	find_package(wxWidgets 3.1 REQUIRED)
	include(${wxWidgets_USE_FILE})
endif()



