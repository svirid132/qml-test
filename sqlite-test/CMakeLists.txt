cmake_minimum_required(VERSION 3.5)

project(sqlite-test LANGUAGES CXX)

find_package(QT NAMES Qt5 Qt6 COMPONENTS Test Sql REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Test Sql REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
enable_testing()

add_executable(sqlite-test sqlite-test.cpp)
add_test(NAME sqlite-test COMMAND sqlite-test)

target_link_libraries(sqlite-test PRIVATE Qt${QT_VERSION_MAJOR}::Test Qt${QT_VERSION_MAJOR}::Sql sqlite)

