cmake_minimum_required(VERSION 4.3)
project(ray_tracer)

set(CMAKE_CXX_STANDARD 20)

add_executable(ray_tracer main.cpp
        Ray.h
        Object.h
        Scene.cpp
        Scene.h
        Sphere.cpp
        Sphere.h
        Camera.cpp
        Camera.h
        Image.cpp
        Image.h
)
