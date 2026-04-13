/* kern_bounce runs a tight loop transitioning between privilege levels */

#include "../shared/fdos/fdos_abi.h"
#include "../arch/x86/fd_x86_msr.h"

/* Main "bounce" loop */

static ulong stack[ 4 ];

__attribute__((noreturn))
__attribute__((naked))
void
bounce_ring0( void ) {
  __asm__ volatile (
    "lretq"
  );
}

__attribute__((noreturn))
__attribute__((naked))
void
bounce_ring3( void ) {
  __asm__ volatile (
    "syscall"
  );
}

/* PMC sampling */

static void
pmc_setup( void ) {
}

__attribute__((noreturn))
void
fdos_kern_main( void ) {
  /* LSTAR (syscall target RIP) */
  fd_x86_wrmsr( FD_X86_MSR_LSTAR, (ulong)bounce_ring0 );

  /* Inter-privilege far return stack arguments */
  stack[ 0 ] = (FDOS_GDT_IDX_USER_DS<<3) + 3; /* ds */
  stack[ 1 ] = (ulong)stack + sizeof(stack);  /* rsp */
  stack[ 2 ] = (FDOS_GDT_IDX_USER_CS<<3) + 3; /* cs */
  stack[ 3 ] = (ulong)bounce_ring3;           /* rip */

  bounce_ring0();
}
