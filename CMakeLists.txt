#[[
    MIT License

    Copyright (c) 2025 Alberto Morcillo Sanz

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
]]

cmake_minimum_required(VERSION 3.10.0...3.22)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

# Project
project(Quant
        VERSION 0.1
        DESCRIPTION "Quant trading"
        HOMEPAGE_URL "https://github.com/MorcilloSanz/Quant"
        LANGUAGES CXX)

message(STATUS "\n${PROJECT_NAME} ${Quant_VERSION}")
message(STATUS ${Quant_DESCRIPTION})
message(STATUS ${Quant_HOMEPAGE_URL})

set (CMAKE_CXX_STANDARD 17)
set(CMAKE_DEBUG_POSTFIX d)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_DEBUG")
add_definitions(-DUNICODE)

# --- GLFW ---
include(FetchContent)

FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.4
)

FetchContent_MakeAvailable(glfw)

# --- GLEW ---
include(FetchContent)

FetchContent_Declare(
    glew
    URL https://github.com/nigels-com/glew/releases/download/glew-2.2.0/glew-2.2.0.zip
)

FetchContent_GetProperties(glew)

if(NOT glew_POPULATED)
    FetchContent_Populate(glew)
endif()

# Compila GLEW estático manualmente
add_library(glew_s STATIC
    ${glew_SOURCE_DIR}/src/glew.c
)

target_include_directories(glew_s PUBLIC
    ${glew_SOURCE_DIR}/include
)

target_compile_definitions(glew_s PUBLIC GLEW_STATIC)

# Para evitar warnings en MSVC
add_definitions(-DGLEW_STATIC)

# third party
add_subdirectory(third_party)
include_directories(third_party)

# Add src
include_directories(src)
add_subdirectory(src)