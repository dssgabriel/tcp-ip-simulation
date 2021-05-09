cmake_minimum_required(VERSION 3.5)

project(Interface LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Charts REQUIRED)

file(GLOB HEADERS
    src/lib/interface/*.h
)
file(GLOB SRCS 
    src/lib/interface/*.cpp
    src/bin/main.cpp
)
add_executable(Interface ${SRCS} ${HEADERS})

target_link_libraries(Interface PRIVATE Qt${QT_VERSION_MAJOR}::Widgets  Qt${QT_VERSION_MAJOR}::Charts)
