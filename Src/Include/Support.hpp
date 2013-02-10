#ifndef __GENERIX_SUPPORT_HPP__
#define __GENERIX_SUPPORT_HPP__

#ifdef __cplusplus
extern "C" {
#endif

#define ATEXIT_MAX_FUNCS	128

typedef int uarch_t;

struct atexit_func_entry_t {
	/*
	 * Each member is at least 4 bytes large. Such that each entry is 12bytes.
	 * 128 * 12 = 1.5KB exact.
	 **/
	void (*destructor_func)(void *);
	void *obj_ptr;
	void *dso_handle;
};

extern void __ctors();
extern void __dtors();
extern int __cxa_atexit(void (*f)(void *), void *objptr, void *dso);
extern void __cxa_finalize(void *f);

#ifdef __cplusplus
}
#endif

#endif //__GENERIX_SUPPORT_HPP__
