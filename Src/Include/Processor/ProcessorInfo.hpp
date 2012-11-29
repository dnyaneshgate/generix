/*
 * ProcessorInfo.hpp
 *
 *  Created on: Oct 8, 2012
 *      Author: dnyanesh
 */

#ifndef __GENERIX_PROCESSORINFO_HPP__
#define __GENERIX_PROCESSORINFO_HPP__

namespace Generix {

/* Vendor-strings. */
#define CPUID_VENDOR_OLDAMD       "AMDisbetter!" //early engineering samples of AMD K5 processor
#define CPUID_VENDOR_AMD          "AuthenticAMD"
#define CPUID_VENDOR_INTEL        "GenuineIntel"
#define CPUID_VENDOR_VIA          "CentaurHauls"
#define CPUID_VENDOR_OLDTRANSMETA "TransmetaCPU"
#define CPUID_VENDOR_TRANSMETA    "GenuineTMx86"
#define CPUID_VENDOR_CYRIX        "CyrixInstead"
#define CPUID_VENDOR_CENTAUR      "CentaurHauls"
#define CPUID_VENDOR_NEXGEN       "NexGenDriven"
#define CPUID_VENDOR_UMC          "UMC UMC UMC "
#define CPUID_VENDOR_SIS          "SiS SiS SiS "
#define CPUID_VENDOR_NSC          "Geode by NSC"
#define CPUID_VENDOR_RISE         "RiseRiseRise"

enum {
    CPUID_GETVENDORSTRING = 0,
    CPUID_GETFEATURES,
    CPUID_GETTLB,
    CPUID_GETSERIAL,
    CPUID_GETCACHE,

    CPUID_INTELEXTENDED = 0x80000000,
    CPUID_INTELFEATURES,
    CPUID_INTELBRANDSTRING,
    CPUID_INTELBRANDSTRINGMORE,
    CPUID_INTELBRANDSTRINGEND,
};

enum {
    CPUID_FEAT_ECX_SSE3 = 1 << 0,
    CPUID_FEAT_ECX_PCLMUL = 1 << 1,
    CPUID_FEAT_ECX_DTES64 = 1 << 2,
    CPUID_FEAT_ECX_MONITOR = 1 << 3,
    CPUID_FEAT_ECX_DS_CPL = 1 << 4,
    CPUID_FEAT_ECX_VMX = 1 << 5,
    CPUID_FEAT_ECX_SMX = 1 << 6,
    CPUID_FEAT_ECX_EST = 1 << 7,
    CPUID_FEAT_ECX_TM2 = 1 << 8,
    CPUID_FEAT_ECX_SSSE3 = 1 << 9,
    CPUID_FEAT_ECX_CID = 1 << 10,
    CPUID_FEAT_ECX_FMA = 1 << 12,
    CPUID_FEAT_ECX_CX16 = 1 << 13,
    CPUID_FEAT_ECX_ETPRD = 1 << 14,
    CPUID_FEAT_ECX_PDCM = 1 << 15,
    CPUID_FEAT_ECX_DCA = 1 << 18,
    CPUID_FEAT_ECX_SSE4_1 = 1 << 19,
    CPUID_FEAT_ECX_SSE4_2 = 1 << 20,
    CPUID_FEAT_ECX_x2APIC = 1 << 21,
    CPUID_FEAT_ECX_MOVBE = 1 << 22,
    CPUID_FEAT_ECX_POPCNT = 1 << 23,
    CPUID_FEAT_ECX_AES = 1 << 25,
    CPUID_FEAT_ECX_XSAVE = 1 << 26,
    CPUID_FEAT_ECX_OSXSAVE = 1 << 27,
    CPUID_FEAT_ECX_AVX = 1 << 28,

    CPUID_FEAT_EDX_FPU = 1 << 0,
    CPUID_FEAT_EDX_VME = 1 << 1,
    CPUID_FEAT_EDX_DE = 1 << 2,
    CPUID_FEAT_EDX_PSE = 1 << 3,
    CPUID_FEAT_EDX_TSC = 1 << 4,
    CPUID_FEAT_EDX_MSR = 1 << 5,
    CPUID_FEAT_EDX_PAE = 1 << 6,
    CPUID_FEAT_EDX_MCE = 1 << 7,
    CPUID_FEAT_EDX_CX8 = 1 << 8,
    CPUID_FEAT_EDX_APIC = 1 << 9,
    CPUID_FEAT_EDX_SEP = 1 << 11,
    CPUID_FEAT_EDX_MTRR = 1 << 12,
    CPUID_FEAT_EDX_PGE = 1 << 13,
    CPUID_FEAT_EDX_MCA = 1 << 14,
    CPUID_FEAT_EDX_CMOV = 1 << 15,
    CPUID_FEAT_EDX_PAT = 1 << 16,
    CPUID_FEAT_EDX_PSE36 = 1 << 17,
    CPUID_FEAT_EDX_PSN = 1 << 18,
    CPUID_FEAT_EDX_CLF = 1 << 19,
    CPUID_FEAT_EDX_DTES = 1 << 21,
    CPUID_FEAT_EDX_ACPI = 1 << 22,
    CPUID_FEAT_EDX_MMX = 1 << 23,
    CPUID_FEAT_EDX_FXSR = 1 << 24,
    CPUID_FEAT_EDX_SSE = 1 << 25,
    CPUID_FEAT_EDX_SSE2 = 1 << 26,
    CPUID_FEAT_EDX_SS = 1 << 27,
    CPUID_FEAT_EDX_HTT = 1 << 28,
    CPUID_FEAT_EDX_TM1 = 1 << 29,
    CPUID_FEAT_EDX_IA64 = 1 << 30,
    CPUID_FEAT_EDX_PBE = 1 << 31
};

struct IntelBrandIndexString {

    IntelBrandIndexString(const UINT b, const UINT s, const char* t) : brand(b), signature(s), text(t)
    {
    }

    const UINT brand;
    const UINT signature; // Not yet supported by this program.
    const CHAR* text;
};

STATIC CONST IntelBrandIndexString intel_brand_index_list[] = {
    IntelBrandIndexString(0x00, 0x0000, "This processor does not support the brand identification feature"),
    IntelBrandIndexString(0x00, 0x06EC, "Intel CoreTM Duo processor"),
    IntelBrandIndexString(0x01, 0x0000, "Intel Celeron processor"),
    IntelBrandIndexString(0x02, 0x0000, "Intel Pentium III processor"),
    IntelBrandIndexString(0x03, 0x0000, "Intel Pentium III XeonTM processor"),
    IntelBrandIndexString(0x03, 0x06B1, "Intel Celeron processor"),
    IntelBrandIndexString(0x04, 0x0000, "Intel Pentium III processor"),
    IntelBrandIndexString(0x06, 0x0000, "Mobile Intel Pentium III processor-M"),
    IntelBrandIndexString(0x07, 0x0000, "Mobile Intel Celeron processor"),
    IntelBrandIndexString(0x08, 0x0000, "Intel Pentium 4 processor"),
    IntelBrandIndexString(0x09, 0x0000, "Intel Pentium 4 processor"),
    IntelBrandIndexString(0x0a, 0x0000, "Intel Celeron processor"),
    IntelBrandIndexString(0x0b, 0x0000, "Intel XeonTM processor"),
    IntelBrandIndexString(0x0b, 0x0F13, "Intel XeonTM processor MP"),
    IntelBrandIndexString(0x0c, 0x0000, "Intel XeonTM processor MP"),
    IntelBrandIndexString(0x0e, 0x0000, "Mobile Intel Pentium 4 processor-M"),
    IntelBrandIndexString(0x0e, 0x0F13, "Intel XeonTM processor"),
    IntelBrandIndexString(0x0f, 0x0000, "Mobile Intel Celeron processor"),
    IntelBrandIndexString(0x13, 0x0000, "Mobile Intel Celeron processor"),
    IntelBrandIndexString(0x16, 0x0000, "Intel Pentium M processor")
};

struct AMD_BrandIndexString {

    AMD_BrandIndexString(const UINT f, const UINT m, const char* t) : family(f), model(m), text(t)
    {
    }

    const UINT family;
    const UINT model;
    const CHAR* text;
};

STATIC CONST AMD_BrandIndexString amd_brand_index_list[] = {
    AMD_BrandIndexString(0x04, 0x00, "Am486 and Am5x86 Processors"),
    AMD_BrandIndexString(0x05, 0x00, "AMD-K5 Model 0"),
    AMD_BrandIndexString(0x05, 0x01, "AMD-K5 Model 1"),
    AMD_BrandIndexString(0x05, 0x02, "AMD-K5 Model 2"),
    AMD_BrandIndexString(0x05, 0x03, "AMD-K5 Model 3"),
    AMD_BrandIndexString(0x05, 0x06, "AMD-K6 Model 6"),
    AMD_BrandIndexString(0x05, 0x07, "AMD-K6 Model 7"),
    AMD_BrandIndexString(0x05, 0x08, "AMD-K6-2 Model 8"),
    AMD_BrandIndexString(0x05, 0x09, "AMD-K6-III Model 9"),
    AMD_BrandIndexString(0x06, 0x01, "AMD Athlon Model 1"),
    AMD_BrandIndexString(0x06, 0x02, "AMD Athlon Model 2"),
    AMD_BrandIndexString(0x06, 0x03, "AMD Duron Model 3"),
    AMD_BrandIndexString(0x06, 0x04, "AMD Athlon Model 4"),
    AMD_BrandIndexString(0x06, 0x06, "AMD Athlon MP Model 6"),
    AMD_BrandIndexString(0x06, 0x06, "AMD Athlon XP Model 6"),
    AMD_BrandIndexString(0x06, 0x06, "Mobile AMD Athlon 4 Model 6"),
    AMD_BrandIndexString(0x06, 0x06, "AMD Duron Model 6"),
    AMD_BrandIndexString(0x06, 0x06, "Mobile AMD Duron Model 6"),
    AMD_BrandIndexString(0x06, 0x07, "AMD Duron Model 7"),
    AMD_BrandIndexString(0x06, 0x07, "Mobile AMD Duron Model 7"),
    AMD_BrandIndexString(0x06, 0x08, "AMD Athlon XP Model 8"),
    AMD_BrandIndexString(0x06, 0x08, "AMD Athlon MP Model 8"),
    AMD_BrandIndexString(0x06, 0x0A, "Mobile AMD Athlon XPM Model 8"),
    AMD_BrandIndexString(0x06, 0x0A, "Mobile AMD Athlon XPM (LV) Model 8"),
    AMD_BrandIndexString(0x06, 0x0A, "AMD Athlon XP Model 10"),
    AMD_BrandIndexString(0x06, 0x0A, "AMD Athlon MP Model 10"),
    AMD_BrandIndexString(0x06, 0x0A, "Mobile AMD Athlon XPM Model 10"),
    AMD_BrandIndexString(0x06, 0x0A, "Mobile AMD Athlon XPM (LV) Model 10"),
    AMD_BrandIndexString(0x0F, 0x04, "AMD Athlon 64 Model 4"),
    AMD_BrandIndexString(0x0F, 0x05, "AMD Opteron Model 5")
};

}

#endif //__GENERIX_PROCESSORINFO_HPP__
