cmake_minimum_required(VERSION 3.18)
#comment
enable_testing()
project(qml-test LANGUAGES CXX)

add_subdirectory(app)
add_subdirectory(sqlite)
add_subdirectory(sqlite-test)

