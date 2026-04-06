cmake_minimum_required(VERSION 3.20)
project(fdos_guest VERSION 0.1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(PICOLIBC_INSTALL_DIR "picolibc install dir" "")
if(NOT PICOLIBC_INSTALL_DIR)
  message(FATAL_ERROR "PICOLIBC_INSTALL_DIR is not defined")
endif()
add_library(picolibc_libc STATIC IMPORTED)
set_target_properties(picolibc_libc PROPERTIES
  IMPORTED_LOCATION "${PICOLIBC_INSTALL_DIR}/lib/libc.a"
  INTERFACE_INCLUDE_DIRECTORIES "${PICOLIBC_INSTALL_DIR}/include")

add_library(fdos_kern STATIC)
target_link_libraries(fdos_kern PUBLIC picolibc_libc)

add_executable(kern_hlt kern_hlt.c)
target_link_libraries(kern_hlt PRIVATE fdos_kern)
