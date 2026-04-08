#pragma once

/* https://www.sandpile.org/x86/apic.htm */

#define FD_X86_APIC_OFF_TPR     0x080 /* task priority register */
#define FD_X86_APIC_OFF_EOI     0x0b0 /* end of interrupt */
#define FD_X86_APIC_OFF_SVR     0x0f0 /* spurious interrupt vector register */
#define FD_X86_APIC_OFF_LVT_PMC 0x340 /* LVT: performance monitoring counter */
