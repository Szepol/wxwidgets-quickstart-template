add_library(
	domain
	domain/reseau/Graph.cc
	domain/reseau/Graph.h
	domain/reseau/Node.cc
	domain/reseau/Node.h
	domain/reseau/ReseauInterurbain.cc
	domain/reseau/ReseauInterurbain.h
	domain/controller/ControllerInput.cc
	domain/controller/ControllerInput.h
	domain/controller/ControllerOutput.cc
	domain/controller/ControllerOutput.h
	domain/controller/Model.cc
	domain/controller/Model.h
	)

add_library(
	gui
	gui/MainWindowFrame.cc
	gui/MainWindowFrame.h
	gui/View.cc
	gui/View.h
	)

if (WIN32)
    add_executable(${PROJECT_NAME} WIN32 App.cc)
else()
    add_executable(${PROJECT_NAME} WIN32 App.cc)
ENDIF()

configure_file("Version.h.in" "Version.h")
include_directories("${PROJECT_BINARY_DIR}/src")
target_include_directories(domain PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(gui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
if(USE_CPM)
    target_link_libraries(domain PUBLIC wxWidgets)
else()
    target_link_libraries(domain PUBLIC ${wxWidgets_LIBRARIES})
endif()
target_link_libraries(gui PRIVATE domain)
target_link_libraries(${PROJECT_NAME} PRIVATE gui)
