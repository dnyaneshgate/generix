#ifndef __GENERIX_LIBC_STRING_H__
#define __GENERIX_LIBC_STRING_H__

#include <sys/types.h>

#ifdef __cplusplus
extern "C" {
#endif

	extern void* memcpy(void* dest, const void* src, size_t n);
	extern void* memcpy_b(void* dest, const void* src, size_t n);
	extern void* memcpy_w(void* dest, const void* src, size_t n);
	extern void* memcpy_l(void* dest, const void* src, size_t n);
	extern void* memmove(void* dest, const void* src, size_t n);
	extern void* memmove_b(void* dest, const void* src, size_t n);
	extern void* memmove_w(void* dest, const void* src, size_t n);
	extern void* memmove_l(void* dest, const void* src, size_t n);
	extern void* memset(void* dest, int val, size_t n);
	extern void* memset_b(void* dest, int val, size_t n);
	extern void* memset_w(void* dest, int val, size_t n);
	extern void* memset_l(void* dest, int val, size_t n);
	extern void* memchr(const void* dest, int c, size_t n);
	extern int strlen(const char* src);
	extern char* strcpy(char* dest, const char* src);
	extern char* strncpy(char* dest, const char* src, size_t n);
	extern char* strcat(char* dest, const char* src);
	extern char* strncat(char* dest, const char* src, size_t n);
	extern int strcmp(const char* s1, const char* s2);
	extern int strncmp(const char* s1, const char* s2, size_t n);
	extern char* strchr(const char* dest, int c);
	extern char* strrchr(const char* dest, int c);
	extern char* strrev(char *str);
	extern size_t strcspn(const char *s1, const char *s2);
	extern size_t strspn(const char *s1, const char *s2);
	extern char* strpbrk(const char *s1, const char *s2);
	extern char* strtok(char *s, const char *delim);
	extern size_t strxfrm(char *dst, char *src, size_t n);
	extern char* strlwr(char *s);
	extern char* strupr(char *s);
	extern void bzero(void *dest, size_t n);

#define strequ(S1,S2) !strcmp(S1,S2)

#ifdef __cplusplus
}
#endif

#endif //__GENERIX_LIBC_STRING_H__
