#ifndef __GENERIX_PROCESSOR_HPP__
#define __GENERIX_PROCESSOR_HPP__

#include "Arch/IOPort.hpp"
#include "Arch/CPU.hpp"
#include "Arch/Interrupt.hpp"
#include "Arch/Timer.hpp"
#include <Singleton.hpp>

namespace Generix {

	typedef enum {
		UNKNOWN = -1,
		INTEL = 0,
		AMD
	} Processor;

	class GProcessorInfo;

	class GProcessor : public GSingleton<GProcessor> {
		friend class GSingleton<GProcessor>;
		friend class GKernel;
	public:
		BOOL InstallPit();
		BOOL RegInterrupt(INT No, IsrHandler isr);
		BOOL SetTimerFreq(UINT Frequency = 1000);
		BOOL GetTickCount(UINT &tick);
		BOOL GetProcessorInfo(const CHAR *info, VOID *result);
		BOOL GetProcessorFeature(const CHAR *feature);
	protected:
	private:
		GProcessor();
		~GProcessor();

		VOID ProcessorInfoInit();

		GProcessorInfo *m_p_ProcessorInfo;
		GTimer m_timer;
	};

	class GProcessorInfo : public GSingleton<GProcessorInfo> {
		friend class GSingleton<GProcessorInfo>;
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
};

#endif //__GENERIX_PROCESSOR_HPP__
