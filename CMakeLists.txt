cmake_minimum_required(VERSION 3.5)

project(Sim-TCP_IP LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Charts REQUIRED)

file(GLOB HEADERS
    src/lib/interface/*.hpp
)

file(GLOB SRCS
    src/lib/interface/*.cpp
    src/bin/main.cpp
)

add_executable(Sim-TCP_IP ${SRCS} ${HEADERS})

target_link_libraries(Sim-TCP_IP PRIVATE Qt${QT_VERSION_MAJOR}::Widgets  Qt${QT_VERSION_MAJOR}::Charts)
