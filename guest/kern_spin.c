__attribute__((noreturn)) void
fdos_kern_main( void ) {
  for(;;) { __asm__ volatile( "pause" ); }
}
