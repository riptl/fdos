__attribute__((noreturn)) void
fdos_kern_main( void ) {
  int * volatile p = (void *)0xdeadbeef;
  *p = 0;
  for(;;) {}
}
