cmake_minimum_required (VERSION 3.14...3.22)

project(
    wxwidgets-quickstart-template
    VERSION 1.0
    LANGUAGES CXX
)

find_package(wxWidgets)

if(wxWidgets_FOUND)
  # Temporary fix for weird MSVC interaction
  if(MSVC)
    if(CMAKE_BUILD_TYPE STREQUAL Debug)
      if(NOT ${wxWidgets_CONFIGURATION} MATCHES .*d$ )
        set(wxWidgets_CONFIGURATION ${wxWidgets_CONFIGURATION}d)
      endif()
    else()
      if(${wxWidgets_CONFIGURATION} MATCHES .*d$ )
        string(LENGTH ${wxWidgets_CONFIGURATION} BUILD_STR_SIZE)
        MATH(EXPR BUILD_STR_SIZE "${BUILD_STR_SIZE}-1")
        string(SUBSTRING ${wxWidgets_CONFIGURATION} 0 ${BUILD_STR_SIZE} wxWidgets_CONFIGURATION)
      endif()
    endif()

    find_package(wxWidgets REQUIRED)
  endif()
  include(${wxWidgets_USE_FILE})
else(NOT wxWidgets_FOUND)
  set(USING_CPM true)
  set(BUILD_SHARED_LIBS OFF)
  set(CPM_DOWNLOAD_VERSION 0.34.0)

  if(CPM_SOURCE_CACHE)
    get_filename_component(CPM_SOURCE_CACHE ${CPM_SOURCE_CACHE} ABSOLUTE)
    set(CPM_DOWNLOAD_LOCATION "${CPM_SOURCE_CACHE}/cpm/CPM_${CPM_DOWNLOAD_VERSION}.cmake")
  elseif(DEFINED ENV{CPM_SOURCE_CACHE})
    set(CPM_DOWNLOAD_LOCATION "$ENV{CPM_SOURCE_CACHE}/cpm/CPM_${CPM_DOWNLOAD_VERSION}.cmake")
  else()
    set(CPM_DOWNLOAD_LOCATION "${CMAKE_BINARY_DIR}/cmake/CPM_${CPM_DOWNLOAD_VERSION}.cmake")
  endif()

  if(NOT (EXISTS ${CPM_DOWNLOAD_LOCATION}))
    message(STATUS "Downloading CPM.cmake to ${CPM_DOWNLOAD_LOCATION}")
    file(DOWNLOAD
      https://github.com/cpm-cmake/CPM.cmake/releases/download/v${CPM_DOWNLOAD_VERSION}/CPM.cmake
      ${CPM_DOWNLOAD_LOCATION}
    )
  endif()

  include(${CPM_DOWNLOAD_LOCATION})

  CPMAddPackage(
    NAME wxWidgets
    GIT_REPOSITORY https://github.com/wxWidgets/wxWidgets
    GIT_TAG        v3.1.6
  )
endif()

add_subdirectory(src)

if(BUILD_TESTING)
  find_package(GTest)
  if (GTest_FOUND)
    include_directories(${GTEST_INCLUDE_DIRS})
  else()
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
    include(GoogleTest)
  endif()
  enable_testing()
  add_subdirectory(tests)
endif()
