target_sources(fd_util PRIVATE
  fd_shmem_admin.c
  fd_shmem_user.c
)
if(NOT FDOS_BARE)
  target_sources(fd_util PRIVATE fd_numa_linux.c)
else()
  target_sources(fd_util PRIVATE fd_numa_stub.c)
endif()

if(BUILD_TESTING)
  add_executable(test_shmem test_shmem.c)
  target_link_libraries(test_shmem PRIVATE fd_util)
  add_test(NAME test_shmem COMMAND test_shmem)
endif()
