#include "../shared/util/log/fd_log.h"

__attribute__((naked)) void
fdos_syscall_handler( void ) {
  __asm__ volatile (
      "movabs $0xffffff80003ffff8UL, %rax\n"
      "mov %rax, %rsp\n"
      "ud2\n" /* TODO */
  );
}

void (* fdos_ring3_enter_ptr)( ulong new_rsp, ulong new_rip )
  = (__typeof__(fdos_ring3_enter_ptr))0x41414141;
