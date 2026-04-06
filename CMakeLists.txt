cmake_minimum_required(VERSION 3.20)
project(fdos VERSION 0.1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

option(FDOS_TESTS "Build tests" OFF)

include(CheckCSourceCompiles)
find_package(Threads REQUIRED)

if(FDOS_TESTS)
  enable_testing()
endif()

add_subdirectory(arch/x86)
add_subdirectory(shared)
add_subdirectory(host)

include(ExternalProject)
ExternalProject_Add(fdos_guest
  SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/guest"
  CMAKE_ARGS "-DCMAKE_TOOLCHAIN_FILE=${CMAKE_CURRENT_SOURCE_DIR}/guest/fdos_x86.cmake"
  INSTALL_COMMAND "")
