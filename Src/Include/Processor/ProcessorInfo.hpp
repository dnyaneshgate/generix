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
	CPUID_GETVENDORSTRING=0,
	CPUID_GETFEATURES,
	CPUID_GETTLB,
	CPUID_GETSERIAL,
	CPUID_GETCACHE,

	CPUID_INTELEXTENDED=0x80000000,
	CPUID_INTELFEATURES,
	CPUID_INTELBRANDSTRING,
	CPUID_INTELBRANDSTRINGMORE,
	CPUID_INTELBRANDSTRINGEND,
};

}

#endif //__GENERIX_PROCESSORINFO_HPP__
