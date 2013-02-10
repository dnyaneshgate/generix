#ifndef __GENERIX_LIBC_STDLIB_H__
#define __GENERIX_LIBC_STDLIB_H__

#ifdef NULL
#undef NULL
#endif

#ifdef CPP
#define NULL 0
#else
#define NULL (void*)0
#endif

#define UNDEFINED NULL
#define EXIT_FAILURE -1
#define EXIT_SUCCESS 0

#ifdef CPP
extern "C" {
#endif

extern int atoi(const char *nptr);
//extern long atol(const char *nptr);
//extern long long atoll(const char *nptr);
//extern long long atoq(const char *nptr);
extern void itoa(char *buf, int base, long long d);

#ifdef CPP
}
#endif

#endif //__GENERIX_LIBC_STDLIB_H__
