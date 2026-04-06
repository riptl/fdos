add_library(fdos STATIC
  fdos_vmm.c
)
target_link_libraries(fdos PUBLIC fd_util)
