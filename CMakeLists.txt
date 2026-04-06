cmake_minimum_required(VERSION 3.20)
project(fdos VERSION 0.1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(FDOS_TESTS "Build tests" OFF)

include(CheckCSourceCompiles)
find_package(Threads REQUIRED)

if(FDOS_TESTS)
  enable_testing()
endif()

if(CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64|AMD64")
  set(FD_HAS_X86 1)

  set(CMAKE_REQUIRED_FLAGS "${_march_flags}")

  check_c_source_compiles("
    #ifndef __AVX2__
    #error
    #endif
    int main(void){return 0;}
  " _has_avx2)
  if(_has_avx2)
    set(FD_HAS_SSE 1)
    set(FD_HAS_AVX 1)
  endif()

  check_c_source_compiles("
    #ifndef __AVX512F__
    #error
    #endif
    int main(void){return 0;}
  " _has_avx512f)
  if(_has_avx512f)
    set(FD_HAS_AVX512 1)
  endif()

  unset(CMAKE_REQUIRED_FLAGS)
endif()

add_subdirectory(arch/x86)
add_subdirectory(shared)

include(ExternalProject)
ExternalProject_Add(fdos_guest
  SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/guest"
  CMAKE_ARGS "-DCMAKE_TOOLCHAIN_FILE=${CMAKE_CURRENT_SOURCE_DIR}/guest/fdos_x86.cmake"
  INSTALL_COMMAND "")
