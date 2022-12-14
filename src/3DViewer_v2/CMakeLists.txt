cmake_minimum_required(VERSION 3.5)

project(3DViewer_v2 VERSION 0.1 LANGUAGES CXX C)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt6 REQUIRED COMPONENTS OpenGLWidgets)
find_package(Qt6 REQUIRED COMPONENTS Gui)

set(TS_FILES 3DViewer_v2_en_US.ts)

set(PROJECT_SOURCES
        main.cpp
        Model_module/model_frame.h
        Model_module/model_frame.cc
        Controller_module/viewer_controller.h
        Controller_module/viewer_controller.cc
        View_module/mainwindow.cc
        View_module/mainwindow.h
        View_module/mainwindow.ui
        View_module/ptransform.h
        View_module/ptransform.cc
        View_module/ptransform.ui
        View_module/viewsetup.h
        View_module/viewsetup.cc
        View_module/viewsetup.ui
        View_module/screencap.h
        View_module/screencap.cc
        View_module/screencap.ui
        View_module/enum_parameters.h
        View_module/oglview.h
        View_module/oglview.cc
        View_module/oglview.ui
        giflib/dgif_lib.c
        giflib/egif_lib.c
        giflib/gif_err.c
        giflib/gif_hash.c
        giflib/gifalloc.c
        giflib/quantize.c
        gifimage/qgifglobal.h
        gifimage/qgifimage.h
        gifimage/qgifimage_p.h
        gifimage/qgifimage.cpp
        ${TS_FILES}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(3DViewer_v2
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET 3DViewer_v2 APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(3DViewer_v2 SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(3DViewer_v2
            ${PROJECT_SOURCES}
        )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

target_link_libraries(3DViewer_v2 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(3DViewer_v2 PRIVATE Qt6::OpenGLWidgets)
target_link_libraries(3DViewer_v2 PRIVATE Qt6::Gui)

set_target_properties(3DViewer_v2 PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(3DViewer_v2)
endif()
