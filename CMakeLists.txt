cmake_minimum_required (VERSION 3.14...3.22)

project(
    ReseauInterurbain
    VERSION 1.0
    LANGUAGES CXX
)

option(USE_CPM "Fetch packages using C++ Package Manager" FALSE)

# TODO
if(USE_CPM)
    set(CPM_DOWNLOAD_VERSION v0.35.0)

    set(CPM_DOWNLOAD_LOCATION "${CMAKE_BINARY_DIR}/cmake/CPM_${CPM_DOWNLOAD_VERSION}.cmake")

    if(NOT (EXISTS ${CPM_DOWNLOAD_LOCATION}))
        message(STATUS "Downloading CPM.cmake to ${CPM_DOWNLOAD_LOCATION}")
        file(DOWNLOAD
            https://github.com/cpm-cmake/CPM.cmake/releases/download/${CPM_DOWNLOAD_VERSION}/CPM.cmake
            ${CPM_DOWNLOAD_LOCATION}
        )
    endif()

    include(${CPM_DOWNLOAD_LOCATION})
    message(STATUS ${CPM_DOWNLOAD_LOCATION})

    CPMAddPackage(
        NAME wxWidgets
        GIT_REPOSITORY https://github.com/wxWidgets/wxWidgets
        GIT_TAG v3.1.6
    )
    if (wxWidgets_ADDED)
        add_library(wxWidgets INTERFACE)
        target_include_directories(wxWidgets INTERFACE "${wxWidgets_SOURCE_DIR}")
    endif()
else()
    find_package(wxWidgets 3.1 REQUIRED)
    include(${wxWidgets_USE_FILE})
endif()

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
endif()



