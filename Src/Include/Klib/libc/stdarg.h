#ifndef __GENERIX_LIBC_STDARG_H__
#define __GENERIX_LIBC_STDARG_H__

#include <va_list.h>

#ifdef CPP
extern "C" {
#endif

/* Amount of space required in an argument list for an arg of type TYPE.
 TYPE may alternatively be an expression whose type is used.  */

#define __va_rounded_size(TYPE)  \
  (((sizeof (TYPE) + sizeof (int) - 1) / sizeof (int)) * sizeof (int))

#ifndef __sparc__
#define va_start(AP, LASTARG) 						\
 (AP = ((va_list) &(LASTARG) + __va_rounded_size (LASTARG)))
#else
#define va_start(AP, LASTARG) 						\
 (__builtin_saveregs (),						\
  AP = ((char *) &(LASTARG) + __va_rounded_size (LASTARG)))
#endif

void va_end(va_list); /* Defined in gnulib */
#define va_end(AP)

#define va_arg(AP, TYPE)						\
 (AP += __va_rounded_size (TYPE),					\
  *((TYPE *) (AP - __va_rounded_size (TYPE))))

#ifdef CPP
}
#endif

#endif //__GENERIX_LIBC_STDARG_H__
