cmake_minimum_required(VERSION 3.5)
project(PIA_terrain)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
set(CMAKE_CXX_STANDARD 11)  # Nebo vyšší
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(findpath main.cpp Path.cpp TerrainMap.cpp Lod.cpp Letadlo.cpp)