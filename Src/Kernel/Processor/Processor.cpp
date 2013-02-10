#include <Types.hpp>
#include <Macros.hpp>
#include <string.h>
#include <ScreenIo.hpp>
#include <Singleton.hpp>
#include <Processor/Processor.hpp>
#include <Processor/ProcessorInfo.hpp>
#define _CPUID(EAX,EBX,ECX,EDX) __ASM__ __VOLATILE__("cpuid":"=a"(EAX),"=b"(EBX),"=c"(ECX),"=d"(EDX):"a"(EAX))
#define CPUID() _CPUID(_EAX,_EBX,_ECX,_EDX)
PRIVATE ULONG _EAX, _EBX, _ECX, _EDX;

namespace Generix {

class GProcessorInfo: public GSingleton<GProcessorInfo> {
	friend class GSingleton<GProcessorInfo> ;
	friend class GProcessor;
private:
	Processor m_i_Processor;
	CHAR m_c_VendorName[13];
	UINT m_u_MaxBasicInput;
	UINT m_u_MaxExtInput;
	UINT m_u_Signature;
	UINT m_u_SteppingId;
	UINT m_u_ModelNumber;
	UINT m_u_FamilyCode;
	UINT m_u_ProcessorType;
	UINT m_u_ExtModel;
	UINT m_u_ExtFamily;
	UINT m_u_Reserved;
	UINT m_u_Cores;
	UINT m_u_ApicId;
	UINT m_u_BrandId;
	UINT m_u_Chunks;
	UINT m_u_Features;

	GProcessorInfo();
	~GProcessorInfo();

	VOID DO_INTEL();
	VOID DO_AMD();

	VOID IntelBasicProcessorInfo();
	VOID IntelExtendedProcessorInfo();

	BOOL GetProcessorFeature(const CHAR *feature);

	CHAR* GetVendorName() const;
	UINT GetProcessorFamilyCode() const;
	UINT GetProcessorModelNumber() const;
	UINT GetProcessorSteppingId() const;
	UINT GetProcessorType() const;
	UINT GetProcessorCores() const;
	UINT GetProcessorExtFamily() const;
	UINT GetProcessorExtModel() const;
	UINT GetProcessorApicId() const;
	UINT GetProcessorBrandId() const;
	CHAR* GetProcessorBrand() const;
};

GProcessor::GProcessor() {
	m_p_ProcessorInfo = GProcessorInfo::Instance();
}

GProcessor::~GProcessor() {
}

BOOL GProcessor::InstallPit() {
	CLI();
	EnableIrq(0, GTimer::TimerHandler);
	m_timer.SetFrequency(1000);
	m_timer.Initialise();
	STI();
	return true;
}

BOOL GProcessor::RegInterrupt(INT x, IsrHandler isr) {
	SetVector(x, isr);
	return true;
}

BOOL GProcessor::SetTimerFreq(UINT freq) {
	m_timer.SetFrequency((ULONG) freq);
	m_timer.Initialise();
	return true;
}

BOOL GProcessor::GetProcessorInfo(const CHAR *info, VOID *result) {
	if (strequ(info, "VendorName")) {
		CHAR *vendorName = m_p_ProcessorInfo->GetVendorName();
		memcpy(result, vendorName, strlen(vendorName));
		return true;
	} else if (strequ(info, "Family")) {
		UINT *res = (UINT*) result;
		*res = m_p_ProcessorInfo->GetProcessorFamilyCode();
		return true;
	} else if (strequ(info, "Model")) {
		UINT *res = (UINT*) result;
		*res = m_p_ProcessorInfo->GetProcessorModelNumber();
		return true;
	} else if (strequ(info, "ExtModel")) {
		UINT *res = (UINT*) result;
		*res = m_p_ProcessorInfo->GetProcessorExtModel();
		return true;
	} else if (strequ(info, "ExtFamily")) {
		UINT *res = (UINT*) result;
		*res = m_p_ProcessorInfo->GetProcessorExtFamily();
		return true;
	} else if (strequ(info, "Cores")) {
		UINT *res = (UINT*) result;
		*res = m_p_ProcessorInfo->GetProcessorCores();
		return true;
	} else if (strequ(info, "SteppingId")) {
		UINT *res = (UINT*) result;
		*res = m_p_ProcessorInfo->GetProcessorSteppingId();
		return true;
	} else if (strequ(info, "Type")) {
		UINT *res = (UINT*) result;
		*res = m_p_ProcessorInfo->GetProcessorType();
		return true;
	} else if (strequ(info, "ApicId")) {
		UINT *res = (UINT*) result;
		*res = m_p_ProcessorInfo->GetProcessorApicId();
		return true;
	} else if (strequ(info, "Brand")) {
		CHAR *BrandName = m_p_ProcessorInfo->GetProcessorBrand();
		memcpy(result, BrandName, strlen(BrandName));
		return true;
	}

	return false;
}

BOOL GProcessor::GetProcessorFeature(const CHAR* feature) {
	return m_p_ProcessorInfo->GetProcessorFeature(feature);
}

GProcessorInfo::GProcessorInfo() {
	_EAX = CPUID_GETVENDORSTRING;
	CPUID();
	*(UINT*) (m_c_VendorName + 0) = (UINT) _EBX;
	*(UINT*) (m_c_VendorName + 4) = (UINT) _EDX;
	*(UINT*) (m_c_VendorName + 8) = (UINT) _ECX;
	m_c_VendorName[12] = ZERO;

	m_u_MaxBasicInput = _EAX;

	if (strequ(m_c_VendorName, CPUID_VENDOR_INTEL)) {
		m_i_Processor = eINTEL;
		DO_INTEL();
	} else if (strequ(m_c_VendorName, CPUID_VENDOR_AMD)) {
		m_i_Processor = eAMD;
		DO_AMD();
	} else {
		m_i_Processor = eUNKNOWN;
	}
}

GProcessorInfo::~GProcessorInfo() {
}

CHAR*
GProcessorInfo::GetVendorName() const {
	return (CHAR*) m_c_VendorName;
}

UINT GProcessorInfo::GetProcessorFamilyCode() const {
	return m_u_FamilyCode;
}

UINT GProcessorInfo::GetProcessorModelNumber() const {
	return m_u_ModelNumber;
}

UINT GProcessorInfo::GetProcessorSteppingId() const {
	return m_u_SteppingId;
}

UINT GProcessorInfo::GetProcessorType() const {
	return m_u_ProcessorType;
}

UINT GProcessorInfo::GetProcessorCores() const {
	return m_u_Cores;
}

UINT GProcessorInfo::GetProcessorExtFamily() const {
	return m_u_ExtFamily;
}

UINT GProcessorInfo::GetProcessorExtModel() const {
	return m_u_ExtModel;
}

UINT GProcessorInfo::GetProcessorApicId() const {
	return m_u_ApicId;
}

UINT GProcessorInfo::GetProcessorBrandId() const {
	return m_u_BrandId;
}

CHAR*
GProcessorInfo::GetProcessorBrand() const {
	CHAR* text = (CHAR*) "Unknown Processor";

	if (m_i_Processor EQU eINTEL) {
		UINT limit = sizeof(intel_brand_index_list)
				/ sizeof(IntelBrandIndexString);
		for (UINT i = 0; i LT limit; i++)
			if ((intel_brand_index_list[i].brand EQU m_u_BrandId)
					and (intel_brand_index_list[i].signature EQU m_u_Signature))
				text = (CHAR*) intel_brand_index_list[i].text;
	} else if (m_i_Processor EQU eAMD) {
		UINT limit = sizeof(amd_brand_index_list)
				/ sizeof(AMD_BrandIndexString);
		for (UINT i = 0; i LT limit; i++)
			if ((amd_brand_index_list[i].family EQU m_u_FamilyCode)
					and (amd_brand_index_list[i].model EQU m_u_ModelNumber))
				text = (CHAR*) amd_brand_index_list[i].text;
	}
	return text;
}

BOOL GProcessorInfo::GetProcessorFeature(const CHAR* feature) {
	return false;
}

VOID GProcessorInfo::DO_INTEL() {
	_EAX = CPUID_GETFEATURES;
	CPUID();

	m_u_Signature = _EAX;
	m_u_SteppingId = _EAX AND 0xF;
	m_u_ModelNumber = SHR(_EAX, 4) AND 0xF;
	m_u_FamilyCode = SHR(_EAX, 8) AND 0xF;
	m_u_ProcessorType = SHR(_EAX, 12) AND 0x3;
	m_u_ExtModel = SHR(_EAX, 16) AND 0xF;
	m_u_ExtFamily = SHR(_EAX, 20) AND 0xFF;
	m_u_Reserved = SHR(_EAX, 14);

	m_u_BrandId = _EBX AND 0xFF;
	m_u_Chunks = SHR(_EBX, 8) AND 0xFF;
	m_u_Cores = SHR(_EBX, 16) AND 0xFF;
	m_u_ApicId = SHR(_EBX, 24) AND 0xFF;

	m_u_Features = _ECX;
}

VOID GProcessorInfo::DO_AMD() {
}
}
