cmake_minimum_required(VERSION 3.16)
project(AnimeManager LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS Widgets Network REQUIRED) # Se usar Qt5, troque Qt6 por Qt5

add_executable(AnimeManager
    main.cpp
    AnimeInfo.h
    DataManager.h DataManager.cpp
    MalApiManager.h MalApiManager.cpp
    SearchResultsModal.h SearchResultsModal.cpp
)

target_link_libraries(AnimeManager PRIVATE Qt6::Widgets Qt6::Network)