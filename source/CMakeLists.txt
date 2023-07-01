cmake_minimum_required(VERSION 3.5)

project(MovieManager VERSION 1.0 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        addrowdialog.cpp
        addrowdialog.h
        addrowdialog.ui
        aboutdialog.h
        aboutdialog.cpp
        aboutdialog.ui
        table.cpp
        table.h
        customproxymodel_rating.cpp
        customproxymodel_rating.h
        customproxymodel_popularity.cpp
        customproxymodel_popularity.h
        MovieManager.rc
)


if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(MovieManager
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )

else()
    if(ANDROID)
        add_library(MovieManager SHARED
            ${PROJECT_SOURCES}
        )

    else()
        add_executable(MovieManager
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(MovieManager PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(MovieManager PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(MovieManager)
endif()
