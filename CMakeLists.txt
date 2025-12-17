cmake_minimum_required(VERSION 4.0.2)
project(Raytracing-Engine)

set(CMAKE_CXX_STANDARD 20)
add_executable(Raytracing-Engine main.cpp
        window2.cpp
        image.cpp
        input.cpp
        sphere.cpp
        camera.cpp)


target_include_directories(Raytracing-Engine
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include)


target_include_directories(Raytracing-Engine PRIVATE include)