#include "../shared/util/fd_util_base.h"

__attribute__((noreturn))
__attribute__((naked))
void
fdos_kern_main( void ) {
  __asm__ volatile (
    "movq $0, %rdi\n"
    "lbl:\n"
    "inc %rdi\n"
    "jmp lbl\n"
  );
}
