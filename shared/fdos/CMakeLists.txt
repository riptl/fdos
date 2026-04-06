add_library(fdos STATIC
  fdos_vmm.c
)
target_link_libraries(fdos PUBLIC fd_util)

add_executable(test_vmm test_vmm.c)
target_link_libraries(test_vmm PRIVATE fdos)
add_test(NAME test_vmm COMMAND test_vmm)
