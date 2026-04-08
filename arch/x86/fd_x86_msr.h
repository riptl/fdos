#pragma once

#define FD_X86_RFLAGS_IDX_PF    2
#define FD_X86_RFLAGS_IDX_TF    8
#define FD_X86_RFLAGS_IDX_IOPL 12

#define FD_X86_RFLAGS_PF    (1UL<<FD_X86_RFLAGS_IDX_PF)
#define FD_X86_RFLAGS_TF    (1UL<<FD_X86_RFLAGS_IDX_TF)
#define FD_X86_RFLAGS_IOPL3 (3UL<<FD_X86_RFLAGS_IDX_IOPL)

#define FD_X86_CR0_PE (1U<<0)
#define FD_X86_CR0_MP (1U<<1)
#define FD_X86_CR0_EM (1U<<2)
#define FD_X86_CR0_TS (1U<<3)
#define FD_X86_CR0_ET (1U<<4)
#define FD_X86_CR0_NE (1U<<5)
#define FD_X86_CR0_WP (1U<<16)
#define FD_X86_CR0_AM (1U<<18)
#define FD_X86_CR0_NW (1U<<29)
#define FD_X86_CR0_CD (1U<<30)
#define FD_X86_CR0_PG (1U<<31)

#define FD_X86_CR4_PAE      (1UL<< 5)
#define FD_X86_CR4_PGE      (1UL<< 7)
#define FD_X86_CR4_OSFXSR   (1UL<< 9)
#define FD_X86_CR4_FSGSBASE (1UL<<16)
#define FD_X86_CR4_OSXSAVE  (1UL<<18)
#define FD_X86_CR4_FRED     (1UL<<32)

#define FD_X86_EFER_SCE (1U<< 0)
#define FD_X86_EFER_LME (1U<< 8)
#define FD_X86_EFER_LMA (1U<<10)
#define FD_X86_EFER_NXE (1U<<11)

#define FD_X86_MSR_FRED_RSP0    0x000001cc
#define FD_X86_MSR_FRED_RSP1    0x000001cd
#define FD_X86_MSR_FRED_RSP2    0x000001ce
#define FD_X86_MSR_FRED_RSP3    0x000001cf
#define FD_X86_MSR_FRED_STKLVLS 0x000001d0
#define FD_X86_MSR_FRED_SSP1    0x000001d1
#define FD_X86_MSR_FRED_SSP2    0x000001d2
#define FD_X86_MSR_FRED_SSP3    0x000001d3
#define FD_X86_MSR_FRED_CONFIG  0x000001d4

#define FD_X86_MSR_EFER          0xc0000080
#define FD_X86_MSR_STAR          0xc0000081
#define FD_X86_MSR_LSTAR         0xc0000082
#define FD_X86_MSR_FSBASE        0xc0000100
#define FD_X86_MSR_PVCLOCK_EPOCH 0x4b564d00
#define FD_X86_MSR_PVCLOCK_OFF   0x4b564d01

#define FD_X86_XCR0_X87       (1U<<0)
#define FD_X86_XCR0_SSE       (1U<<1)
#define FD_X86_XCR0_AVX       (1U<<2)
#define FD_X86_XCR0_OPMASK    (1U<<5)
#define FD_X86_XCR0_ZMM_HI256 (1U<<6)
#define FD_X86_XCR0_HI16_ZMM  (1U<<7)

#define FD_X86_MSR_PMC0                           0x000000c1
#define FD_X86_MSR_PERFEVTSEL0                    0x00000186
#define FD_X86_MSR_PERFEVTSEL1                    0x00000187
#define FD_X86_MSR_PERFEVTSEL2                    0x00000188
#define FD_X86_MSR_PERFEVTSEL3                    0x00000189
#define FD_X86_MSR_DEBUGCTL                       0x000001d9
#define FD_X86_MSR_FIXED_CTR0                     0x00000309
#define FD_X86_MSR_FIXED_CTR1                     0x0000030a
#define FD_X86_MSR_FIXED_CTR2                     0x0000030b
#define FD_X86_MSR_FIXED_CTR3                     0x0000030c
#define FD_X86_MSR_FIXED_CTR_CTRL                 0x0000038d
#define FD_X86_MSR_PERF_GLOBAL_STATUS             0x0000038e
#define FD_X86_MSR_PERF_GLOBAL_CTRL               0x0000038f
#define FD_X86_MSR_PERF_GLOBAL_OVF_CTRL           0x00000390
#define FD_X86_MSR_PERF_GLOBAL_STATUS_RESET       0x00000390
#define FD_X86_MSR_PERF_GLOBAL_STATUS_SET         0x00000391
#define FD_X86_MSR_PERF_GLOBAL_INUSE              0x00000392
#define FD_X86_MSR_F15H_PERF_CTRL0                0xc0010200 /* AMD Zen PMC */
#define FD_X86_MSR_F15H_PERF_CTR0                 0xc0010201
#define FD_X86_MSR_F15H_PERF_CTRL1                0xc0010202
#define FD_X86_MSR_F15H_PERF_CTR1                 0xc0010203
#define FD_X86_MSR_F15H_PERF_CTRL2                0xc0010204
#define FD_X86_MSR_F15H_PERF_CTR2                 0xc0010205
#define FD_X86_MSR_F15H_PERF_CTRL3                0xc0010206
#define FD_X86_MSR_F15H_PERF_CTR3                 0xc0010207
#define FD_X86_MSR_F15H_PERF_CTRL4                0xc0010208
#define FD_X86_MSR_F15H_PERF_CTR4                 0xc0010209
#define FD_X86_MSR_F15H_PERF_CTRL5                0xc001020a
#define FD_X86_MSR_F15H_PERF_CTR5                 0xc001020b
#define FD_X86_MSR_AMD64_PERF_GLOBAL_STATUS       0xc0000300 /* AMD Zen PMC config */
#define FD_X86_MSR_AMD64_PERF_GLOBAL_CTRL         0xc0000301
#define FD_X86_MSR_AMD64_PERF_GLOBAL_STATUS_CLR   0xc0000302
#define FD_X86_MSR_AMD64_PERF_GLOBAL_STATUS_SET   0xc0000303
