set(CMAKE_SYSTEM_NAME Linux)

set(CMAKE_C_COMPILER clang)
set(CMAKE_C_COMPILER_TARGET x86_64-unknown-elf)
set(CMAKE_LINKER ld.lld)

set(CMAKE_C_LINK_EXECUTABLE
  "<CMAKE_LINKER> <CMAKE_C_LINK_FLAGS> <LINK_FLAGS> <OBJECTS> -o <TARGET> <LINK_LIBRARIES>")

execute_process(
  COMMAND ${CMAKE_C_COMPILER} --print-resource-dir
  OUTPUT_VARIABLE CLANG_RESOURCE_DIR
  OUTPUT_STRIP_TRAILING_WHITESPACE)

set(CMAKE_C_FLAGS_INIT
  "-march=x86-64-v2 \
  -mtune=generic \
  --no-default-config \
  -ffreestanding \
  -fno-plt \
  -fno-pie \
  -fno-pic \
  -static \
  -fno-common \
  -nostdinc \
  -isystem ${CLANG_RESOURCE_DIR}/include \
  -nostdlib \
  -nostartfiles \
  -nodefaultlibs \
  -mno-red-zone \
  -mcmodel=kernel \
  -minvpcid"
)

set(CMAKE_EXE_LINKER_FLAGS_INIT
  "--no-undefined \
  --no-dynamic-linker \
  --static \
  -T ${CMAKE_CURRENT_SOURCE_DIR}/fdos_x86.ld \
  -u fdos_kern_entry_idt")

set(CMAKE_C_COMPILER_WORKS 1)
