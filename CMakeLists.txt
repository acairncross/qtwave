cmake_minimum_required(VERSION 3.5)

project(qtwave VERSION 0.0.0 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        src/main.cpp
        src/mainwindow.cpp
        src/mainwindow.h
        src/vcdparser.cpp
        src/vcdparser.h
        src/freezetablewidget.h
        src/freezetablewidget.cpp
        src/waveformdelegate.h
        src/waveformdelegate.cpp
        src/waveformitem.h
        src/waveformitem.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(qtwave
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    add_executable(qtwave
        ${PROJECT_SOURCES}
    )
endif()

target_link_libraries(qtwave PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(qtwave PROPERTIES
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS qtwave
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(qtwave)
endif()
