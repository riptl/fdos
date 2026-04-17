/* kern_bounce runs a tight loop transitioning between privilege levels */

#include "../shared/fdos/fdos_abi.h"
#include "../arch/x86/fd_x86_msr.h"
#include "../arch/x86/fd_x86_pmc.h"

/* Main "bounce" loop */

static ulong stack[ 4 ];

void
bounce_ring3( void );

__attribute__((noreturn))
__attribute__((naked))
void
bounce_ring0( void ) {
  __asm__ volatile (
    "sysretq\n"
    : : "c" ((ulong)bounce_ring3)
  );
}

__attribute__((noreturn))
__attribute__((naked))
void
bounce_ring3( void ) {
  __asm__ volatile (
    "syscall\n"
  );
}

__attribute__((noreturn))
void
fdos_kern_main( void ) {
  /* LSTAR (syscall target RIP) */
  fd_x86_wrmsr( FD_X86_MSR_LSTAR, (ulong)bounce_ring0 );

  // fd_x86_wrmsr( FD_X86_MSR_F15H_PERF_CTRL0, (0x0076) |
  //     FD_X86_PMC_SEL_EN  |
  //     FD_X86_PMC_SEL_OS );

  // fd_x86_wrmsr( FD_X86_MSR_F15H_PERF_CTRL1, (0x00c0) |
  //     FD_X86_PMC_SEL_EN  |
  //     FD_X86_PMC_SEL_OS );

  // fd_x86_wrmsr( FD_X86_MSR_AMD64_PERF_GLOBAL_CTRL, 3UL );

  /* Inter-privilege far return stack arguments */
  // ulong rsp = (ulong)stack;
  // stack[ 3 ] = (FDOS_GDT_IDX_USER_DS<<3) + 3; /* ds */
  // stack[ 2 ] = (ulong)rsp;                    /* rsp */
  // stack[ 1 ] = (FDOS_GDT_IDX_USER_CS<<3) + 3; /* cs */
  // stack[ 0 ] = (ulong)bounce_ring3;           /* rip */

  __asm__ volatile (
    // "mov %0, %%rsp\n"
    "jmp bounce_ring0\n"
    // : : "r" (rsp)
  );
}
