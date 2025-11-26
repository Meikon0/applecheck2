cmake_minimum_required(VERSION 3.16)
project(AppleCheck LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Allow building with Qt6 or Qt5.15 (Aurora compatible)
find_package(Qt6 COMPONENTS Quick Multimedia REQUIRED QUIET)
set(QT_PREFIX Qt6)
if(NOT Qt6_FOUND)
    find_package(Qt5 5.15 COMPONENTS Quick Multimedia REQUIRED)
    set(QT_PREFIX Qt5)
endif()

set(SOURCES
    src/main.cpp
    src/ui_controller.cpp
    src/image_classifier.cpp
)

set(HEADERS
    src/ui_controller.h
    src/image_classifier.h
)

qt_add_resources(QML_RESOURCES qml/qml.qrc)

if(${QT_PREFIX} STREQUAL "Qt6")
    qt_add_executable(AppleCheck
        ${SOURCES}
        ${HEADERS}
        ${QML_RESOURCES}
    )
    target_link_libraries(AppleCheck
        PRIVATE
            Qt6::Quick
            Qt6::Multimedia
    )
else()
    add_executable(AppleCheck
        ${SOURCES}
        ${HEADERS}
        ${QML_RESOURCES}
    )
    target_link_libraries(AppleCheck
        PRIVATE
            Qt5::Quick
            Qt5::Multimedia
    )
endif()

install(TARGETS AppleCheck)
