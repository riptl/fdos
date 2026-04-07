cmake_minimum_required(VERSION 3.20)
project(fdos VERSION 0.1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

include(CheckCSourceCompiles)
find_package(Threads REQUIRED)
find_package(LLVM CONFIG QUIET)

set(FDOS_BARE OFF)

include(CTest)

add_subdirectory(arch/x86)
add_subdirectory(shared/fdos)
add_subdirectory(shared/util)
add_subdirectory(host)

include(ExternalProject)

ExternalProject_Add(picolibc
  GIT_REPOSITORY    https://github.com/picolibc/picolibc.git
  GIT_TAG           1.8.11
  CONFIGURE_COMMAND meson setup --wipe
    --cross-file ${CMAKE_CURRENT_SOURCE_DIR}/guest/fdos_x86.meson
    <BINARY_DIR> <SOURCE_DIR>
    -Dmultilib=false
    -Dpicocrt=false
    -Dinitfini-array=false
    -Dthread-local-storage=false
    -Dsingle-thread=true
    -Dsemihost=false
    -Dio-float-exact=false
    -Dprefix=<INSTALL_DIR>
  BUILD_COMMAND   meson compile -C <BINARY_DIR>
  INSTALL_COMMAND meson install -C <BINARY_DIR>
  UPDATE_DISCONNECTED TRUE
  CONFIGURE_HANDLED_BY_BUILD TRUE)
ExternalProject_Get_Property(picolibc INSTALL_DIR)
set(PICOLIBC_INSTALL_DIR "${INSTALL_DIR}")
unset(INSTALL_DIR)

ExternalProject_Add(fdos_guest
  SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/guest"
  CMAKE_ARGS
    -DCMAKE_TOOLCHAIN_FILE=${CMAKE_CURRENT_SOURCE_DIR}/guest/fdos_x86.cmake
    -DCMAKE_INSTALL_PREFIX=<INSTALL_DIR>
    -DPICOLIBC_INSTALL_DIR=${PICOLIBC_INSTALL_DIR}
    -DBUILD_TESTING=OFF
  BUILD_ALWAYS TRUE
  CONFIGURE_HANDLED_BY_BUILD TRUE)
add_dependencies(fdos_guest picolibc)
