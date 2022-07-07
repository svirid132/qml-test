cmake_minimum_required(VERSION 3.14)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core Sql REQUIRED)

add_library(sqlite
        sqlitemanager.cpp
        sqlrenamer.cpp
        res.qrc
        )

target_include_directories(sqlite
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
        )

target_link_libraries(sqlite PRIVATE Qt5::Core Qt5::Sql)

if (CMAKE_BUILD_TYPE STREQUAL "Release")
    install(TARGETS sqlite)
endif ()
