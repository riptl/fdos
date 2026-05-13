/* kern_bounce runs a tight loop transitioning between privilege levels */

#include "../shared/fdos/fdos_abi.h"
#include "../arch/x86/fd_x86_msr.h"
#include "../arch/x86/fd_x86_pmc.h"

/* Main "bounce" loop */

static ulong stack[ 4 ];

static ulong counter;

void
bounce_ring3( void );

__attribute__((noreturn))
__attribute__((naked))
void
bounce_ring0_sysret( void ) {
  __asm__ volatile (
    "mov %rdi, %rcx\n"
    "sysretq\n"
  );
}

__attribute__((noreturn))
__attribute__((naked))
void
bounce_ring0_lretq( void ) {
  __asm__ volatile (
    "lretq\n"
  );
}

__attribute__((noreturn))
__attribute__((naked))
void
bounce_ring3( void ) {
  __asm__ volatile (
    "incq 0(%rsi)\n"
    "syscall\n"
    "ud2\n"
  );
}

__attribute__((noreturn))
static void
start_sysret( void ) {
  fd_x86_wrmsr( FD_X86_MSR_LSTAR, (ulong)bounce_ring0_sysret );

  ulong rip = (ulong)bounce_ring3;
  __asm__ volatile (
    "jmp bounce_ring0_sysret\n"
    : : "D" (rip), "S" (&counter)
  );
  __builtin_unreachable();
}

__attribute__((noreturn))
static void
start_lretq( void ) {
  fd_x86_wrmsr( FD_X86_MSR_LSTAR, (ulong)bounce_ring0_lretq );

  /* Inter-privilege far return stack arguments */
  ulong rsp = (ulong)stack;
  stack[ 3 ] = (FDOS_GDT_IDX_USER_DS<<3) + 3; /* ds */
  stack[ 2 ] = (ulong)rsp;                    /* rsp */
  stack[ 1 ] = (FDOS_GDT_IDX_USER_CS<<3) + 3; /* cs */
  stack[ 0 ] = (ulong)bounce_ring3;           /* rip */

  __asm__ volatile (
    "mov %0, %%rsp\n"
    "jmp bounce_ring0_lretq\n"
    : : "r" (rsp)
  );
  __builtin_unreachable();
}

__attribute__((noreturn))
void
fdos_kern_main( void ) {
  fd_x86_wrmsr( FD_X86_MSR_F15H_PERF_CTRL0, (0x0076) |
      FD_X86_PMC_SEL_EN  |
      FD_X86_PMC_SEL_OS );

  fd_x86_wrmsr( FD_X86_MSR_F15H_PERF_CTRL1, (0x00c0) |
      FD_X86_PMC_SEL_EN  |
      FD_X86_PMC_SEL_OS );

  fd_x86_wrmsr( FD_X86_MSR_AMD64_PERF_GLOBAL_CTRL, 3UL );

  start_sysret(); /* ~ 38.2 cycle per round trip (Zen 5)*/
  // start_lretq(); /* ~80 cycle per round trip (Zen 5) */
}

/* 7.33 cycles/instruction

   syscall
   inc qword ptr [rsi]
   mov rcx, rdi
   sysretq
   inc qword ptr [rsi]

   11.00 cycles/instruction

   syscall
   mov rcx, rdi
   sysretq
   inc qword ptr [rsi]   */
