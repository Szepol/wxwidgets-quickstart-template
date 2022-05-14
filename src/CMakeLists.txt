add_library(
  ui
  ui/MainWindowFrame.cc
  ui/MainWindowFrame.h
)

if(WIN32)
  add_executable(${PROJECT_NAME} WIN32 App.cc)
else()
  add_executable(${PROJECT_NAME} App.cc)
ENDIF()

configure_file("Version.h.in" "Version.h")
target_include_directories(ui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} "${PROJECT_BINARY_DIR}/src")
if(USING_CPM)
  target_link_libraries(ui PUBLIC wx::core wx::base)
else()
  target_link_libraries(ui PUBLIC ${wxWidgets_LIBRARIES})
endif()
target_link_libraries(${PROJECT_NAME} PRIVATE ui)
