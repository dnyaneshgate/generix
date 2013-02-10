#ifndef __GENERIX_LIBC_STDIO_H__
#define __GENERIX_LIBC_STDIO_H__

#ifdef CPP
extern "C" {
#endif

extern int printf(const char* fmt, ...)
		__attribute__((format(printf, 1, 2)));
extern int sprintf(char* buff, const char* fmt, ...)
		__attribute__((format(printf, 2, 3)));

#ifdef CPP
}
#endif

#endif //__GENERIX_LIBC_STDIO_H__
