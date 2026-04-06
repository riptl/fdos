cmake_minimum_required(VERSION 3.20)
project(fdos_guest VERSION 0.1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(FDOS_BARE ON)
set(BUILD_TESTING OFF)

option(PICOLIBC_INSTALL_DIR "picolibc install dir" "")
if(NOT PICOLIBC_INSTALL_DIR)
  message(FATAL_ERROR "PICOLIBC_INSTALL_DIR is not defined")
endif()

string(APPEND CMAKE_C_FLAGS " -isystem ${PICOLIBC_INSTALL_DIR}/include")
string(APPEND CMAKE_EXE_LINKER_FLAGS " ${PICOLIBC_INSTALL_DIR}/lib/libc.a")

string(APPEND CMAKE_C_FLAGS " -DFD_ENV_STYLE=1 -DFD_LOG_STYLE=1 -DFD_IO_STYLE=1")

add_subdirectory(../shared/fdos ${CMAKE_CURRENT_BINARY_DIR}/shared/fdos)
add_subdirectory(../shared/util ${CMAKE_CURRENT_BINARY_DIR}/shared/util)

add_library(fdos_kern STATIC
  fdos_ctx.c
  fdos_ctx_fred.c
  fdos_ctx_idt.c
  fdos_kern_io.c
  fdos_kern_log.c
)
set_target_properties(fdos_kern PROPERTIES LINK_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/fdos_x86.ld")
target_link_libraries(fdos_kern PUBLIC fd_util)

add_executable(kern_hlt kern_hlt.c)
target_link_libraries(kern_hlt PRIVATE fdos_kern)
install(TARGETS kern_hlt DESTINATION bin)
