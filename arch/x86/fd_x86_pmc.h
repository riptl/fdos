#pragma once

#define FD_X86_PMC_USR (1UL<<16) /* user mode */
#define FD_X86_PMC_OS  (1UL<<17) /* operating system mode */
#define FD_X86_PMC_E   (1UL<<18) /* edge detect */
#define FD_X86_PMC_PC  (1UL<<19) /* pin control */
#define FD_X86_PMC_INT (1UL<<20) /* APIC interrupt enable */
#define FD_X86_PMC_ANY (1UL<<21) /* any thread */
#define FD_X86_PMC_EN  (1UL<<22) /* enable */
#define FD_X86_PMC_INV (1UL<<23) /* invert counter mask */
