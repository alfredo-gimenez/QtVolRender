set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")
set(CMAKE_AUTOMOC ON)
#set(CMAKE_AUTOUIC ON) # tested, not working

# Includes, Definitions, Flags
include_directories(${Qt5Widgets_INCLUDE_DIRS})
add_definitions(${Qt5Widgets_DEFINITIONS})

# ui files
qt5_wrap_ui(ui_form.h form.ui)

# Sources and UI Files
set(SOURCES
  util.cpp
  dataobject.cpp
  glwidget.cpp
  scatterplotviz.cpp
  mainwindow.cpp
  main.cpp)

set(HEADERS
  util.h
  dataobject.h
  glwidget.h
  scatterplotviz.h
  mainwindow.h)

set(UIC
  ui_form.h)

# Build Target
add_executable(VizWidget ${SOURCES} ${HEADERS} ${UIC})

qt5_use_modules(VizWidget Widgets OpenGL)

target_link_libraries(VizWidget Qt5::Widgets Qt5::OpenGL ${OPENGL_LIBRARIES})