#ifndef __GENERIX_MACROS_HPP__
#define __GENERIX_MACROS_HPP__

#ifdef __cplusplus
#define C "C"
#else
#define C
#endif

#define SUCCESS                1
#define FAILED                 0
#define ERROR                  -1

#define _MAX_SIZE              1024
#define BUFFSIZE               _MAX_SIZE

#define STATIC                 static
#define EXTERN                 extern
#define PRIVATE                STATIC
#define FORWORD                STATIC
#define PUBLIC

#define __PACKED__             __attribute__((packed))
#define __SECTION__(x)         __attribute__((section(x)))
#define __USED__               __attribute__((used))
#define __UNUSED__             __attribute__((unused))
#define __ALIGN__(x)           __attribute__((align((x))))

#define __INITFUNC__(x)        __SECTION__(x)
#define __INIT__(level)        __INITFUNC__(".init" level)

#define MAX(x,y)               (((x) > (y)) ? (x) : (y))
#define MIN(x,y)               (((x) < (y)) ? (x) : (y))

#define AND                    &
#define OR                     |
#define XOR                    ^
#define NEG(x)                 (~(x))
#define LT                     <
#define GT                     >
#define LTE                    <=
#define GTE                    >=
#define EQU                    ==
#define NOT                    !

#define BIT(i)                 (1 << (i))
#define BITSET(x,i)            UINT((x)) OR (i)
#define BITRESET(x,i)          UINT((x)) AND NEG(i)

#define ZERO                   0

#define SHL(x,i)               ((x) << (i))
#define SHR(x,i)               ((x) >> (i))

#ifdef __x86__
#define ROL(x,i)               (((x) << (i)) | ((x) >> (32-(i))))
#define ROR(x,i)               (((x) >> (i)) | ((x) << (32-(i))))
#elif __x86_64__
#define ROL(x,i)               (((x) << (i)) | ((x) >> (64-(i))))
#define ROR(x,i)               (((x) >> (i)) | ((x) << (64-(i))))
#else
#error Unsupported Architecture
#endif

#define __ASM__                asm
#define __VOLATILE__           volatile
#define __INTEL_INLINE_ASSEMBLY__ __ASM__(".intel_syntax noprefix")
#define __ATNT_INLINE_ASSEMBLY__  __ASM__(".att_syntax prefix")

#define BREAK                  break
#define CONST                  const
#define SIZEOF					sizeof

#define XSTR(x)					STR(x)
#define STR(x)					#x

#define _PASTE(x,y)				x##y
#define PASTE(x,y)				_PASTE(x,y)

#define SAFE_DELETE_OBJECT(x) \
	if(x)\
	{\
		delete x;\
		x = ZERO;\
	}

#define SAFE_DELETE_ARRAY(x) \
	if(x)\
	{\
		delete[] x;\
		x = ZERO;\
	}

#define SWAP(x,y) \
		{ \
			if((x) != (y)) { \
				x ^= y; \
				y ^= x; \
				x ^= y; \
			} \
		}

#define PSWAP(type,x,y) \
		{ \
			type t = *x; \
			*x = *y; \
			*y = temp; \
		}

#endif //__GENERIX_MACROS_HPP__
