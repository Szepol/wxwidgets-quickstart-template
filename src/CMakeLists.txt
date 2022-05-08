add_library(
	domain
	domain/reseau/Graph.cpp
	domain/reseau/Graph.h
	domain/reseau/Node.cpp
	domain/reseau/Node.h
	domain/reseau/ReseauInterurbain.cpp
	domain/reseau/ReseauInterurbain.h
	domain/controller/ControllerInput.cpp
	domain/controller/ControllerInput.h
	domain/controller/ControllerOutput.cpp
	domain/controller/ControllerOutput.h
	domain/controller/Model.cpp
	domain/controller/Model.h
	)

add_library(
	gui
	gui/MainWindowFrame.cpp
	gui/MainWindowFrame.h
	gui/View.cpp
	gui/View.h
	)
if (WIN32)
	add_executable(${PROJECT_NAME} WIN32 App.h App.cpp)
ENDIF()

target_include_directories(domain PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(gui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(domain PUBLIC ${wxWidgets_LIBRARIES})
target_link_libraries(gui PRIVATE ${wxWidgets_LIBRARIES} domain)
target_link_libraries(${PROJECT_NAME} PRIVATE ${wxWidgets_LIBRARIES} gui)
