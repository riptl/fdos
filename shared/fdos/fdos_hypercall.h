#include "fdos_abi.h"

static inline void
fdos_hypercall_write( int          fd,
                      void const * buf,
                      ulong        len ) {
  __asm__ volatile (
    "movw $" FD_EXPAND_THEN_STRINGIFY( FDOS_HYPERCALL_WRITE ) ", %%dx;\n"
    "pushq %[len];\n"
    "pushq %[buf];\n"
    "pushq %[fd];\n"
    "movq %%rsp, %%rsi;\n"
    "outsl;\n"
    "addq $24, %%rsp;\n"
    :
    : [fd] "r" ((ulong)fd), [buf] "r" (buf), [len] "r" (len)
    : "rsi", "rdx", "memory"
  );
}
