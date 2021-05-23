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
    src/lib/gestion_fichiers/*.hpp
    src/lib/reseau_graphe/*.hpp
    src/lib/reseau_graphe/ospf/*.hpp
    src/lib/reseau_graphe/machine/*.hpp
    src/lib/horloge/*.hpp
    src/lib/protocole_tcp_ip/internet/*.hpp
    src/lib/protocole_tcp_ip/physique/*.hpp
    src/lib/protocole_tcp_ip/transport/*.hpp
    src/include/*.hpp
)

file(GLOB SRCS
    src/lib/interface/*.cpp
    src/lib/gestion_fichiers/*.cpp
    src/lib/reseau_graphe/*.cpp
    src/lib/reseau_graphe/ospf/*.cpp
    src/lib/reseau_graphe/machine/*.cpp
    src/lib/horloge/*.cpp
    src/lib/protocole_tcp_ip/internet/*.cpp
    src/lib/protocole_tcp_ip/physique/*.cpp
    src/lib/protocole_tcp_ip/transport/*.cpp
    src/include/*.cpp
    src/bin/main.cpp
)

add_executable(Sim-TCP_IP ${SRCS} ${HEADERS})

target_link_libraries(Sim-TCP_IP PRIVATE Qt${QT_VERSION_MAJOR}::Widgets  Qt${QT_VERSION_MAJOR}::Charts)
