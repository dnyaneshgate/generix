#ifndef __GENERIX_TYPES_HPP__
#define __GENERIX_TYPES_HPP__

#ifndef __ASSEMBLER__

#ifndef CPP

typedef enum {
	false, true
}bool;
#endif

typedef enum {
	FALSE = 0, TRUE
} Boolean;

typedef char CHAR;
typedef short int SHORT;
typedef int INT;
typedef long LONG;
typedef long long LLONG;

typedef char *string;

typedef CHAR s8;
typedef SHORT s16;
typedef INT s32;
typedef LLONG s64;

typedef s8 int8_t;
typedef s16 int16_t;
typedef s32 int32_t;
typedef s64 int64_t;

typedef unsigned char UCHAR;
typedef unsigned short USHORT;
typedef unsigned int UINT;
typedef unsigned long ULONG;
typedef unsigned long long ULLONG;

typedef UCHAR u8;
typedef USHORT u16;
typedef UINT u32;
typedef ULLONG u64;

typedef u8 uint8_t;
typedef u16 uint16_t;
typedef u32 uint32_t;
typedef u64 uint64_t;

typedef uint8_t BYTE;
typedef uint16_t WORD;
typedef uint32_t DWORD;
typedef uint64_t QWORD;

typedef UINT Size;
typedef ULONG Address;
typedef USHORT UserId;
typedef USHORT GroupId;
typedef USHORT ProcessId;
typedef USHORT PORT;
typedef ULONG Error;
typedef Address PAddress;
typedef Address VAddress;

typedef void VOID;
typedef VOID* Type;
typedef bool BOOL;

typedef VOID *PVOID;
typedef CHAR *PCHAR;
typedef INT *PINT;
typedef LONG *PLONG;
typedef SHORT *PSHORT;
typedef UCHAR *PUCHAR;
typedef USHORT *PUSHORT;
typedef UINT *PUINT;
typedef ULONG *PULONG;
typedef PCHAR STRING;

typedef const char CCHAR;
typedef const char *PCCHAR;
typedef const char *CSTRING;

#endif //__ASSEMBLER__
#endif //__GENERIX_TYPES_HPP__
