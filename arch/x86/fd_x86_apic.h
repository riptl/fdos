#pragma once

/* https://www.sandpile.org/x86/apic.htm */

#define FD_X86_APIC_OFF_TPR        0x080 /* task priority register */
#define FD_X86_APIC_OFF_EOI        0x0b0 /* end of interrupt */
#define FD_X86_APIC_OFF_SVR        0x0f0 /* spurious interrupt vector register */
#define FD_X86_APIC_OFF_LVT_TIMER  0x320 /* LVT: timer */
#define FD_X86_APIC_OFF_LVT_PMC    0x340 /* LVT: performance monitoring counter */
#define FD_X86_APIC_OFF_TIMER_INIT 0x380 /* timer initial count */
#define FD_X86_APIC_OFF_TIMER_CUR  0x390 /* timer current count */
#define FD_X86_APIC_OFF_TIMER_DIV  0x3e0 /* timer divide configuration */

/* Local Vector Table Register Format */

#define FD_X86_APIC_LVT_VEC_SHIFT   0  /* interrupt vector */
#define FD_X86_APIC_LVT_VEC_MASK 0xff
#define FD_X86_APIC_LVT_MT_SHIFT    8  /* message type */
#define FD_X86_APIC_LVT_MT_MASK     7
#define FD_X86_APIC_LVT_TGM  (1UL<<15) /* trigger mode */
#define FD_X86_APIC_LVT_M    (1UL<<16) /* mask */
#define FD_X86_APIC_LVT_TMM  (1UL<<17) /* timer mode */

/* LVT Message Type */

#define FD_X86_APIC_MT_FIXED 0 /* fixed (specified by vector field) */
#define FD_X86_APIC_MT_SMI   2 /* system management interrupt */
#define FD_X86_APIC_MT_NMI   4 /* non-maskable interrupt */
#define FD_X86_APIC_MT_EXT   7 /* external interrupt */
