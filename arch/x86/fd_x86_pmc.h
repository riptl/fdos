#pragma once

#include "../../shared/util/bits/fd_bits.h"

/* PerfEvtSel* */

#define FD_X86_PMC_SEL_MASK      (fd_ulong_mask( 0,  8 ))
#define FD_X86_PMC_SEL_UNIT_MASK (fd_ulong_mask( 8, 16 ))
#define FD_X86_PMC_SEL_USR       (1UL<<16) /* user mode */
#define FD_X86_PMC_SEL_OS        (1UL<<17) /* operating system mode */
#define FD_X86_PMC_SEL_EDGE      (1UL<<18) /* edge detect */
#define FD_X86_PMC_SEL_PC        (1UL<<19) /* pin control */
#define FD_X86_PMC_SEL_INT       (1UL<<20) /* interrupt enable */
#define FD_X86_PMC_SEL_ANY       (1UL<<21) /* any thread */
#define FD_X86_PMC_SEL_EN        (1UL<<22) /* enable */
#define FD_X86_PMC_SEL_INV       (1UL<<23) /* invert counter mask */
#define FD_X86_PMC_SEL_CNT_MASK  (fd_ulong_mask( 24, 32 ))

/* PerfCntGlobalStatus */

#define FD_X86_PMC_STS_LBRSF (1UL<<58) /* last branch record stack freeze */
#define FD_X86_PMC_STS_PMCF  (1UL<<59) /* performance counter freeze */
