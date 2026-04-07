ENTRY(0)
OUTPUT_FORMAT(elf64-x86-64)

PHDRS
{
  ROM  PT_LOAD FLAGS(4);
  CODE PT_LOAD FLAGS(5);
  RAM  PT_LOAD FLAGS(6);
}

SECTIONS
{
  . = 0xffffffff80000000;

  .text : AT(ADDR(.text) - 0xffffffff80000000) {
    *(.text)
    . = ALIGN(4K);
  } :CODE

  .rodata : AT(ADDR(.rodata) - 0xffffffff80000000) {
    *(.rodata)
    *(.rodata.*)
    BYTE(0);
    . = ALIGN(4K);
  } :ROM

  .data : AT(ADDR(.data) - 0xffffffff80000000) {
    *(.data)
    . = ALIGN(4K);
  } :RAM

  .bss (NOLOAD) : AT(ADDR(.bss) - 0xffffffff80000000) {
    *(.bss)
    . = ALIGN(4K);
    __bss_end__ = .;
  } :RAM

  /DISCARD/ :
  {
    *(.note.GNU-stack)
    *(.comment)
    *(.interp)
    *(.hash)
    *(.gnu.hash)
    *(.debug*)
    *(.got) *(.igot.*)
  }
}
