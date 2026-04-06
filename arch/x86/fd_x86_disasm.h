#pragma once

#define FD_X86_DISASM_MAX 512

#if FD_HAS_LIBLLVM

#include "../../shared/util/fd_util_base.h"

ulong
fd_x86_disasm( uchar const * code,
               ulong         rem,
               char          str[ FD_X86_DISASM_MAX ],
               ulong         rip );

#endif /* FD_HAS_LIBLLVM */
