cmake_minimum_required(VERSION 3.14)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Sql REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Sql REQUIRED)

add_library(sqlite
        sqlitemanager.cpp
        sqlrenamer.cpp
        res.qrc
        )

target_include_directories(sqlite
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
        )

target_link_libraries(sqlite PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Sql)

if (CMAKE_BUILD_TYPE STREQUAL "Release")
    install(TARGETS sqlite)
endif ()
