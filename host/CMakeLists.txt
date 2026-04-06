add_library(fdos_host STATIC
  fdos_cpuid.c
  fdos_env.c
  fdos_kern_img.c
  fdos_kvm_init.c
  fdos_kvm.c
)
target_link_libraries(fdos_host PUBLIC fdos fdos_x86)

add_executable(host_kvm host_kvm.c)
target_link_libraries(host_kvm PRIVATE fdos_host)
