cmake_minimum_required(VERSION 3.5)

project(glftest_a LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SOURCES "include/*.h" "src/*.cpp")

add_executable(glftest_a src/main.cpp ${SOURCES})

install(TARGETS glftest_a
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
