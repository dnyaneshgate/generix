/* -*- Mode: C++; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * cpp-kernel
 * Copyright (C) Dnyanesh Gate 2012 <dnyanesh@localhost.localdomain>
 * 
 */

#ifndef __GENERIX_MULTIBOOT_HPP__
#define __GENERIX_MULTIBOOT_HPP__

/* How many bytes from the start of the file we search for the header. */
     #define MULTIBOOT_SEARCH                        8192
     
     /* The magic field should contain this. */
     #define MULTIBOOT_HEADER_MAGIC                  0x1BADB002
     
     /* This should be in %eax. */
     #define MULTIBOOT_BOOTLOADER_MAGIC              0x2BADB002
     
     /* The bits in the required part of flags field we don't support. */
     #define MULTIBOOT_UNSUPPORTED                   0x0000fffc
     
     /* Alignment of multiboot modules. */
     #define MULTIBOOT_MOD_ALIGN                     0x00001000
     
     /* Alignment of the multiboot info structure. */
     #define MULTIBOOT_INFO_ALIGN                    0x00000004
     
     /* Flags set in the 'flags' member of the multiboot header. */
     
     /* Align all boot modules on i386 page (4KB) boundaries. */
     #define MULTIBOOT_PAGE_ALIGN                    0x00000001
     
     /* Must pass memory information to OS. */
     #define MULTIBOOT_MEMORY_INFO                   0x00000002
     
     /* Must pass video information to OS. */
     #define MULTIBOOT_VIDEO_MODE                    0x00000004
     
     /* This flag indicates the use of the address fields in the header. */
     #define MULTIBOOT_AOUT_KLUDGE                   0x00010000
     
     /* Flags to be set in the 'flags' member of the multiboot info structure. */
     
     /* is there basic lower/upper memory information? */
     #define MULTIBOOT_INFO_MEMORY                   0x00000001
     /* is there a boot device set? */
     #define MULTIBOOT_INFO_BOOTDEV                  0x00000002
     /* is the command-line defined? */
     #define MULTIBOOT_INFO_CMDLINE                  0x00000004
     /* are there modules to do something with? */
     #define MULTIBOOT_INFO_MODS                     0x00000008
     
     /* These next two are mutually exclusive */
     
     /* is there a symbol table loaded? */
     #define MULTIBOOT_INFO_AOUT_SYMS                0x00000010
     /* is there an ELF section header table? */
     #define MULTIBOOT_INFO_ELF_SHDR                 0X00000020
     
     /* is there a full memory map? */
     #define MULTIBOOT_INFO_MEM_MAP                  0x00000040
     
     /* Is there drive info? */
     #define MULTIBOOT_INFO_DRIVE_INFO               0x00000080
     
     /* Is there a config table? */
     #define MULTIBOOT_INFO_CONFIG_TABLE             0x00000100
     
     /* Is there a boot loader name? */
     #define MULTIBOOT_INFO_BOOT_LOADER_NAME         0x00000200
     
     /* Is there a APM table? */
     #define MULTIBOOT_INFO_APM_TABLE                0x00000400
     
     /* Is there video information? */
     #define MULTIBOOT_INFO_VIDEO_INFO               0x00000800

typedef struct strucELFHEADERTABLE
{
	unsigned int                    num;		//Number of section headers
	unsigned int                    size;		//Size of each section header
	unsigned int                    addr;		//The address of the first section header
	unsigned int                    shndx;		//Section header string table index
} __attribute__((packed)) ELFHEADERTABLE, *PELFHEADER;

typedef struct strucAOUTSYMBOLTABLE
{
	unsigned int                    tabsize;
	unsigned int                    strsize;
	unsigned int                    addr;
	unsigned int                    reserved;
} __attribute__((packed)) AOUTSYMBOLTABLE, *PAOUTSYMBOLTABLE;

//Bochs 2.4 doesn't provide a ROM configuration table. Virtual PC does.
typedef struct strucROMCONFIGURATIONTABLE
{
	unsigned short                  Length;
	unsigned char                   Model;
	unsigned char                   Submodel;
	unsigned char                   BiosRevision;
	bool                            DualBus : 1;
	bool                            MicroChannelBus : 1;
	bool                            EBDAExists : 1;
	bool                            WaitForExternalEventSupported : 1;
	bool                            Reserved0 : 1;
	bool                            HasRTC : 1;
	bool                            MultipleInterruptControllers : 1;
	bool                            BiosUsesDMA3 : 1;
	bool                            Reserved1 : 1;
	bool                            DataStreamingSupported : 1;
	bool                            NonStandardKeyboard : 1;
	bool                            BiosControlCpu : 1;
	bool                            BiosGetMemoryMap : 1;
	bool                            BiosGetPosData : 1;
	bool                            BiosKeyboard : 1;
	bool                            DMA32Supported : 1;
	bool                            ImlSCSISupported : 1;
	bool                            ImlLoad : 1;
	bool                            InformationPanelInstalled : 1;
	bool                            SCSISupported : 1;
	bool                            RomToRamSupported : 1;
	bool                            Reserved2 : 3;
	bool                            ExtendedPOST : 1;
	bool                            MemorySplit16MB : 1;
	unsigned char                   Reserved3 : 1;
	unsigned char                   AdvancedBIOSPresence : 3;
	bool                            EEPROMPresent : 1;
	bool                            Reserved4 : 1;
	bool                            FlashEPROMPresent : 1;
	bool                            EnhancedMouseMode : 1;
	unsigned char Reserved5 : 6;
} __attribute__((packed)) ROMCONFIGURATIONTABLE, *PROMCONFIGURATIONTABLE;

typedef struct strucMODULE
{
	int                             ModuleStart;
	int                             ModuleEnd;
	char                            *Name;
	unsigned int                    Reserved;
} __attribute__((packed)) MODULE, *PMODULE;

typedef struct strucMEMORYMAP
{
	unsigned int                    Size;
	unsigned int                    BaseAddressLow;
	unsigned int                    BaseAddressHigh;
	unsigned int                    LengthLow;
	unsigned int                    LengthHigh;
	unsigned int                    Type;
} __attribute__((packed)) MEMORYMAP, *PMEMORYMAP;

typedef struct strucDRIVESTRUCTURE
{
	unsigned int                    Size;
	unsigned char                   DriveNumber;
	unsigned char                   Mode;
	unsigned short                  Cylinders;
	unsigned char                   Heads;
	unsigned char                   Sectors;	//Following this field is a list of ports used by the drive, terminating in zero. This means that the Size field has to be used, not sizeof()
} __attribute__((packed)) DRIVESTRUCTURE, *PDRIVESTRUCTURE;

typedef struct strucAPMTABLE
{
	unsigned short                  Version;
	unsigned short                  CS;
	unsigned int                    Offset;
	unsigned short                  CS16Bit;	//This is the 16-bit protected mode code segment
	unsigned short                  DS;
	unsigned short                  Flags;
	unsigned short                  CSLength;
	unsigned short                  CS16BitLength;
	unsigned short                  DSLength;
} __attribute__((packed)) APMTABLE, *PAPMTABLE;

typedef struct strucVBEINFOBLOCK
{
	char                            Signature[4];
	unsigned short                  Version;
	short                           OEMString[2];
	unsigned char                   Capabilities[4];
	short                           VideoModes[2];
	short                           TotalMemory;
} __attribute__((packed)) VBEINFOBLOCK, *PVBEINFOBLOCK;

typedef struct strucVBEMODEINFO
{
	unsigned short                  Attributes;
	unsigned char                   WinA;
	unsigned char                   WinB;
	unsigned short                  Granularity;
	unsigned short                  WinSize;
	unsigned short                  SegmentA;
	unsigned short                  SegmentB;
	unsigned short                  WindowFunctionPointer[2];
	unsigned short                  Pitch;
	unsigned short                  XResolution;
	unsigned short                  YResolution;
	unsigned char                   CharacterWidth;
	unsigned char                   CharacterHeight;
	unsigned char                   Planes;
	unsigned char                   BitsPerPixel;
	unsigned char                   Banks;
	unsigned char                   MemoryModel;
	unsigned char                   BankSize;
	unsigned char                   ImagePages;
	unsigned char                   Reserved;

	unsigned char                   RedMask;
	unsigned char                   RedPosition;

	unsigned char                   GreenMask;
	unsigned char                   GreenPosition;

	unsigned char                   BlueMask;
	unsigned char                   BluePosition;

	unsigned char                   ReservedMask;
	unsigned char                   ReservedPosition;

	unsigned char                   DirectColorAttributes;

	unsigned int                    FrameBuffer;
} __attribute__((packed)) VBEMODEINFO, *PVBEMODEINFO;

typedef struct strucMULTIBOOTIFO
{
	unsigned int                    Flags;
	unsigned int                    MemoryLow;
	unsigned int                    MemoryHigh;
	unsigned int                    BootDevice;
	char                            *CommandLine;
	unsigned int                    ModuleCount;
	MODULE                          *Modules;
	//unsigned int Modules;
	union
	{
		AOUTSYMBOLTABLE             AOUTTable;
		ELFHEADERTABLE              ELFTable;
	} SymbolTables;
	unsigned int                    MemoryMapLength;
	unsigned int                    MemoryMapAddress;
	unsigned int                    DrivesLength;
	PDRIVESTRUCTURE                 DrivesAddress;
	PROMCONFIGURATIONTABLE          ConfigTable;
	char                            *BootloaderName;
	PAPMTABLE                       APMtable;
	PVBEINFOBLOCK                   VBEControlInformation;
	PVBEMODEINFO                    VBEModeInformation;
	unsigned short                  VBEMode;
	unsigned int                    VBEInterfaceAddress;
	unsigned short                  VBEInterfaceLength;
} __attribute__((packed)) MULTIBOOTINFO, *PMULTIBOOTINFO;

typedef struct strucMULTIBOOTHEADER
{
	/* Must be MULTIBOOT_MAGIC - see above. */
	int                             magic;

	/* Feature flags. */
	int                             flags;

	/* The above fields plus this one must equal 0 mod 2^32. */
	int                             checksum;

	/* These are only valid if MULTIBOOT_AOUT_KLUDGE is set. */
	int                             header_addr;
	int                             load_addr;
	int                             load_end_addr;
	int                             bss_end_addr;
	int                             entry_addr;

	/* These are only valid if MULTIBOOT_VIDEO_MODE is set. */
	int                             mode_type;
	int                             width;
	int                             height;
	int                             depth;
}__attribute__((packed)) MULTIBOOTHEADER, *PMULTIBOOTHEADER;

#endif //__GENERIX_MULTIBOOT_HPP__
