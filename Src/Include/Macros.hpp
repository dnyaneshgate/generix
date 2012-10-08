#ifndef __GENERIX_MACROS_HPP__
#define __GENERIX_MACROS_HPP__

#define STATIC                 static
#define EXTERN                 extern
#define PRIVATE                STATIC
#define FORWORD                STATIC
#define PUBLIC

#define __PACKED__             __attribute__((packed))
#define __SECTION__(x)         __attribute__((section(x)))
#define __USED__               __attribute__((used))
#define __UNUSED__             __attribute__((unused))

#define __INIT__               __SECTION__((".initGenerix"))

#define MAX(x,y)               (((x) > (y)) ? (x) : (y))
#define MIN(x,y)               (((x) < (y)) ? (x) : (y))

#define BIT(i)                 (1 << (i))

#define ZERO                   0

#define SHL(x,i)               ((x) << (i))
#define SHR(x,i)               ((x) >> (i))

#define ROL(x,i)               (((x) << (i)) | ((x) >> (32-(i))))
#define ROR(x,i)               (((x) >> (i)) | ((x) << (32-(i))))

#define __ASM__                asm
#define __VOLATILE__           volatile

#define BREAK                  break

#endif //__GENERIX_MACROS_HPP__
