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

if(LLVM_FOUND)
  target_sources(fdos_host PRIVATE ${CMAKE_SOURCE_DIR}/arch/x86/fd_x86_disasm.c)
  target_include_directories(fdos_host PRIVATE ${LLVM_INCLUDE_DIRS})
  target_link_libraries(host_kvm PRIVATE LLVM)
  target_compile_definitions(fdos_host PUBLIC FD_HAS_LIBLLVM=1)
endif()
