__attribute__((naked))
void
fdos_kern_main( void ) {
  __asm__ volatile (
    "movq $-1, %rax;\n"
    "movq %rax, %cr4;\n"
  );
}
