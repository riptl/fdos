#pragma once

#include "../shared/util/fd_util_base.h"

/* FDOS_CPU_FEAT_* give features that require special CPU configuration
   (e.g. presence of AVX512F implies existence of zmm regs, which
   require XCR0 bits) */

#define FDOS_CPU_FEAT_REG_XMM (1UL<<0)
#define FDOS_CPU_FEAT_REG_YMM (1UL<<1)
#define FDOS_CPU_FEAT_REG_ZMM (1UL<<2)
#define FDOS_CPU_FEAT_FRED    (1UL<<3)
#define FDOS_CPU_FEAT_APX     (1UL<<4)
#define FDOS_CPU_FEAT_VNMI    (1UL<<5)
#define FDOS_CPU_FEAT_PMCVIRT (1UL<<6)

struct fdos_cpuid_check {
  ulong cpu_feat;

  uint cpuid_01_0 : 1;
  uint cpuid_07_0 : 1;
  uint cpuid_07_1 : 1;
  uint cpuid_8000_0a : 1;
};

typedef struct fdos_cpuid_check fdos_cpuid_check_t;

void
fdos_cpuid_check_init( fdos_cpuid_check_t * check );

void
fdos_cpuid_check_push( fdos_cpuid_check_t * check,
                       uint                 leaf,
                       uint                 subleaf,
                       uint                 eax,
                       uint                 ebx,
                       uint                 ecx,
                       uint                 edx );

void
fdos_cpuid_validate( fdos_cpuid_check_t const * check );
