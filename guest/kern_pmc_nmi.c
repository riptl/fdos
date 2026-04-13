#include "../shared/fdos/fdos_abi.h"
#include "../shared/fdos/fdos_pvclock.h"
#include "../shared/util/fd_util.h"
#include "../arch/x86/fd_x86_msr.h"
#include "../arch/x86/fd_x86_pmc.h"

static struct {
  uint running    : 1;
  uint nmi_active : 1;
} volatile flags;

static ulong nmi_cnt;

static void
arm_pmc( void ) {
  fd_x86_wrmsr( FD_X86_MSR_F15H_PERF_CTR0, -(long)10000L );

  fd_x86_wrmsr( FD_X86_MSR_AMD64_PERF_GLOBAL_CTRL, 1UL );
}

void
nmi_handler1( void ) {
  if( FD_UNLIKELY( flags.nmi_active ) ) __asm__ volatile("ud2");
  flags.nmi_active = 1;
  if( FD_UNLIKELY( !flags.running ) ) return;
  nmi_cnt++;
  arm_pmc();
  FD_COMPILER_MFENCE();
  flags.nmi_active = 0;
}

__attribute__((naked))
void
nmi_handler( void ) {
  __asm__ volatile (
    /* save all GPRs */
    "push %rdi;\n"
    "push %rsi;\n"
    "push %rbp;\n"
    "push %rdx;\n"
    "push %rcx;\n"
    "push %rax;\n"
    "push %r8;\n"
    "push %r9;\n"
    "push %r10;\n"
    "push %r11;\n"
    "push %r12;\n"
    "push %r13;\n"
    "push %r14;\n"
    "push %r15;\n"
    "call nmi_handler1;\n"
    "pop %r15;\n"
    "pop %r14;\n"
    "pop %r13;\n"
    "pop %r12;\n"
    "pop %r11;\n"
    "pop %r10;\n"
    "pop %r9;\n"
    "pop %r8;\n"
    "pop %rax;\n"
    "pop %rcx;\n"
    "pop %rdx;\n"
    "pop %rbp;\n"
    "pop %rsi;\n"
    "pop %rdi;\n"
    "ret;\n"
  );
}

__attribute__((aligned(256)))
__attribute__((naked))
void
fdos_interrupt_handlers( void ) {
# define SNIP               \
    "leaq 0(%rip), %rsi;\n" \
    "movl $2, %edx;\n"      \
    "outsl;\n"              \
    ".p2align 4;\n"
  __asm__ volatile (
    /* 0x00 */ SNIP /* 0x01 */ SNIP

    /* 0x02 (NMI): ignore */
    "call nmi_handler;\n"
    "iretq;\n"
    ".p2align 4;\n"

    /* 0x03 */ SNIP
    /* 0x04 */ SNIP /* 0x05 */ SNIP /* 0x06 */ SNIP /* 0x07 */ SNIP
    /* 0x08 */ SNIP /* 0x09 */ SNIP /* 0x0a */ SNIP /* 0x0b */ SNIP
    /* 0x0c */ SNIP /* 0x0d */ SNIP /* 0x0e */ SNIP /* 0x0f */ SNIP
    /* 0x10 */ SNIP /* 0x11 */ SNIP /* 0x12 */ SNIP /* 0x13 */ SNIP
    /* 0x14 */ SNIP /* 0x15 */ SNIP /* 0x16 */ SNIP /* 0x17 */ SNIP
    /* 0x18 */ SNIP /* 0x19 */ SNIP /* 0x1a */ SNIP /* 0x1b */ SNIP
    /* 0x1c */ SNIP /* 0x1d */ SNIP /* 0x1e */ SNIP /* 0x1f */ SNIP
    /* 0x20 */ SNIP /* 0x21 */ SNIP /* 0x22 */ SNIP /* 0x23 */ SNIP
    /* 0x24 */ SNIP /* 0x25 */ SNIP /* 0x26 */ SNIP /* 0x27 */ SNIP
    /* 0x28 */ SNIP /* 0x29 */ SNIP /* 0x2a */ SNIP /* 0x2b */ SNIP
    /* 0x2c */ SNIP /* 0x2d */ SNIP /* 0x2e */ SNIP /* 0x2f */ SNIP
    /* 0x30 */ SNIP /* 0x31 */ SNIP /* 0x32 */ SNIP /* 0x33 */ SNIP
    /* 0x34 */ SNIP /* 0x35 */ SNIP /* 0x36 */ SNIP /* 0x37 */ SNIP
    /* 0x38 */ SNIP /* 0x39 */ SNIP /* 0x3a */ SNIP /* 0x3b */ SNIP
    /* 0x3c */ SNIP /* 0x3d */ SNIP /* 0x3e */ SNIP /* 0x3f */ SNIP
    /* 0x40 */ SNIP /* 0x41 */ SNIP /* 0x42 */ SNIP /* 0x43 */ SNIP
    /* 0x44 */ SNIP /* 0x45 */ SNIP /* 0x46 */ SNIP /* 0x47 */ SNIP
    /* 0x48 */ SNIP /* 0x49 */ SNIP /* 0x4a */ SNIP /* 0x4b */ SNIP
    /* 0x4c */ SNIP /* 0x4d */ SNIP /* 0x4e */ SNIP /* 0x4f */ SNIP
    /* 0x50 */ SNIP /* 0x51 */ SNIP /* 0x52 */ SNIP /* 0x53 */ SNIP
    /* 0x54 */ SNIP /* 0x55 */ SNIP /* 0x56 */ SNIP /* 0x57 */ SNIP
    /* 0x58 */ SNIP /* 0x59 */ SNIP /* 0x5a */ SNIP /* 0x5b */ SNIP
    /* 0x5c */ SNIP /* 0x5d */ SNIP /* 0x5e */ SNIP /* 0x5f */ SNIP
    /* 0x60 */ SNIP /* 0x61 */ SNIP /* 0x62 */ SNIP /* 0x63 */ SNIP
    /* 0x64 */ SNIP /* 0x65 */ SNIP /* 0x66 */ SNIP /* 0x67 */ SNIP
    /* 0x68 */ SNIP /* 0x69 */ SNIP /* 0x6a */ SNIP /* 0x6b */ SNIP
    /* 0x6c */ SNIP /* 0x6d */ SNIP /* 0x6e */ SNIP /* 0x6f */ SNIP
    /* 0x70 */ SNIP /* 0x71 */ SNIP /* 0x72 */ SNIP /* 0x73 */ SNIP
    /* 0x74 */ SNIP /* 0x75 */ SNIP /* 0x76 */ SNIP /* 0x77 */ SNIP
    /* 0x78 */ SNIP /* 0x79 */ SNIP /* 0x7a */ SNIP /* 0x7b */ SNIP
    /* 0x7c */ SNIP /* 0x7d */ SNIP /* 0x7e */ SNIP /* 0x7f */ SNIP
    /* 0x80 */ SNIP /* 0x81 */ SNIP /* 0x82 */ SNIP /* 0x83 */ SNIP
    /* 0x84 */ SNIP /* 0x85 */ SNIP /* 0x86 */ SNIP /* 0x87 */ SNIP
    /* 0x88 */ SNIP /* 0x89 */ SNIP /* 0x8a */ SNIP /* 0x8b */ SNIP
    /* 0x8c */ SNIP /* 0x8d */ SNIP /* 0x8e */ SNIP /* 0x8f */ SNIP
    /* 0x90 */ SNIP /* 0x91 */ SNIP /* 0x92 */ SNIP /* 0x93 */ SNIP
    /* 0x94 */ SNIP /* 0x95 */ SNIP /* 0x96 */ SNIP /* 0x97 */ SNIP
    /* 0x98 */ SNIP /* 0x99 */ SNIP /* 0x9a */ SNIP /* 0x9b */ SNIP
    /* 0x9c */ SNIP /* 0x9d */ SNIP /* 0x9e */ SNIP /* 0x9f */ SNIP
    /* 0xa0 */ SNIP /* 0xa1 */ SNIP /* 0xa2 */ SNIP /* 0xa3 */ SNIP
    /* 0xa4 */ SNIP /* 0xa5 */ SNIP /* 0xa6 */ SNIP /* 0xa7 */ SNIP
    /* 0xa8 */ SNIP /* 0xa9 */ SNIP /* 0xaa */ SNIP /* 0xab */ SNIP
    /* 0xac */ SNIP /* 0xad */ SNIP /* 0xae */ SNIP /* 0xaf */ SNIP
    /* 0xb0 */ SNIP /* 0xb1 */ SNIP /* 0xb2 */ SNIP /* 0xb3 */ SNIP
    /* 0xb4 */ SNIP /* 0xb5 */ SNIP /* 0xb6 */ SNIP /* 0xb7 */ SNIP
    /* 0xb8 */ SNIP /* 0xb9 */ SNIP /* 0xba */ SNIP /* 0xbb */ SNIP
    /* 0xbc */ SNIP /* 0xbd */ SNIP /* 0xbe */ SNIP /* 0xbf */ SNIP
    /* 0xc0 */ SNIP /* 0xc1 */ SNIP /* 0xc2 */ SNIP /* 0xc3 */ SNIP
    /* 0xc4 */ SNIP /* 0xc5 */ SNIP /* 0xc6 */ SNIP /* 0xc7 */ SNIP
    /* 0xc8 */ SNIP /* 0xc9 */ SNIP /* 0xca */ SNIP /* 0xcb */ SNIP
    /* 0xcc */ SNIP /* 0xcd */ SNIP /* 0xce */ SNIP /* 0xcf */ SNIP
    /* 0xd0 */ SNIP /* 0xd1 */ SNIP /* 0xd2 */ SNIP /* 0xd3 */ SNIP
    /* 0xd4 */ SNIP /* 0xd5 */ SNIP /* 0xd6 */ SNIP /* 0xd7 */ SNIP
    /* 0xd8 */ SNIP /* 0xd9 */ SNIP /* 0xda */ SNIP /* 0xdb */ SNIP
    /* 0xdc */ SNIP /* 0xdd */ SNIP /* 0xde */ SNIP /* 0xdf */ SNIP
    /* 0xe0 */ SNIP /* 0xe1 */ SNIP /* 0xe2 */ SNIP /* 0xe3 */ SNIP
    /* 0xe4 */ SNIP /* 0xe5 */ SNIP /* 0xe6 */ SNIP /* 0xe7 */ SNIP
    /* 0xe8 */ SNIP /* 0xe9 */ SNIP /* 0xea */ SNIP /* 0xeb */ SNIP
    /* 0xec */ SNIP /* 0xed */ SNIP /* 0xee */ SNIP /* 0xef */ SNIP
    /* 0xf0 */ SNIP /* 0xf1 */ SNIP /* 0xf2 */ SNIP /* 0xf3 */ SNIP
    /* 0xf4 */ SNIP /* 0xf5 */ SNIP /* 0xf6 */ SNIP /* 0xf7 */ SNIP
    /* 0xf8 */ SNIP /* 0xf9 */ SNIP /* 0xfa */ SNIP /* 0xfb */ SNIP
    /* 0xfc */ SNIP /* 0xfd */ SNIP /* 0xfe */ SNIP /* 0xff */ SNIP
  );
# undef SNIP
}

static fd_pvclock_t * g_pvclock;

__attribute__((noreturn))
void
fdos_kern_main( fdos_kern_args_t * args ) {
  g_pvclock = (fd_pvclock_t *)args->pvclock_gvaddr;
  fd_log_thread_set( "kvm0" );
  fd_log_wallclock_set( fd_pvclock_now, g_pvclock );
  fd_log_colorize_set( 1 );

  fd_x86_wrmsr( FD_X86_MSR_F15H_PERF_CTRL0, (0x0076) |
      FD_X86_PMC_INT |
      FD_X86_PMC_EN  |
      FD_X86_PMC_OS );

  fd_x86_wrmsr( FD_X86_MSR_F15H_PERF_CTR0, -(long)100000L );

  fd_x86_wrmsr( FD_X86_MSR_AMD64_PERF_GLOBAL_CTRL, 1UL );

  long dt = -fd_tickcount();
  ulong const limit = 1UL<<32UL;
  flags.running = 1;
  for( ulong i=0UL; i<limit; i++ ) {
    __asm__ ( "nop" : : : "memory" );
  }
  dt += fd_tickcount();
  FD_LOG_NOTICE(( "%g NMIs handled", (double)nmi_cnt ));
  FD_LOG_NOTICE(( "%g iterations in %g ticks", (double)limit, (double)dt ));
  FD_LOG_ERR(( "Done" ));
  for(;;) {}
}
