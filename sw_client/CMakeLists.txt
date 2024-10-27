cmake_minimum_required(VERSION 3.16)

project(SW_Client1 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find necessary Qt components
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets SerialPort Test)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets SerialPort Test)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(SW_Client1
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(SW_Client1 SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(SW_Client1
            ${PROJECT_SOURCES}
        )
    endif()
endif()

# Link the main application libraries
target_link_libraries(SW_Client1 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::SerialPort)

# Set macOS/iOS bundle properties
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.SW_Client1)
endif()
set_target_properties(SW_Client1 PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# Installation paths
include(GNUInstallDirs)
install(TARGETS SW_Client1
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Finalize executable for Qt 6
if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(SW_Client1)
endif()

# Add include directories for tests to find main files
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Add the test executable
add_executable(tests
    tests/test_mainwindow.cpp
    mainwindow.cpp
    mainwindow.h
)

# Link test libraries
target_link_libraries(tests PRIVATE Qt${QT_VERSION_MAJOR}::Test Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::SerialPort)

set_target_properties(sw_client PROPERTIES AUTOMOC ON)
set_target_properties(tests PROPERTIES AUTOMOC ON)

enable_testing()

add_test(NAME TestSerialCommunication COMMAND tests)
