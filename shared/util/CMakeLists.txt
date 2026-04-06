add_library(fd_util STATIC
  fd_hash.c
  fd_util.c
)

target_include_directories(fd_util PUBLIC ${PROJECT_SOURCE_DIR}/src)
target_link_libraries(fd_util PUBLIC Threads::Threads m rt dl)

target_compile_definitions(fd_util PUBLIC
  FD_HAS_HOSTED=1
  FD_HAS_ATOMIC=1
  FD_HAS_THREADS=1
  FD_HAS_INT128=1
  FD_HAS_DOUBLE=1
  FD_HAS_ALLOCA=1
)

if(FDOS_TESTS)
  add_executable(test_util test_util.c)
  target_link_libraries(test_util PRIVATE fd_util)
  add_test(NAME test_util COMMAND test_util)

  add_executable(test_util_base test_util_base.c)
  target_link_libraries(test_util_base PRIVATE fd_util)
  add_test(NAME test_util_base COMMAND test_util_base)
endif()

add_subdirectory(bits)
add_subdirectory(cstr)
add_subdirectory(env)
add_subdirectory(io)
add_subdirectory(log)
add_subdirectory(math)
add_subdirectory(pod)
add_subdirectory(rng)
add_subdirectory(scratch)
add_subdirectory(shmem)
add_subdirectory(tile)
add_subdirectory(tpool)
add_subdirectory(wksp)
