__attribute__((noreturn)) void
fdos_kern_main( void ) {
  __asm__ volatile( "hlt" );
  __builtin_unreachable();
}
