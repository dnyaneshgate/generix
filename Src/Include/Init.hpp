#ifndef __GENERIX_INIT_HPP__
#define __GENERIX_INIT_HPP__

#include <Types.hpp>
#include <Macros.hpp>

#define INITFUNC(func) \
				STATIC ULONG _initcall_##func __INIT__ USED = (ULONG) func

#define INITCLASS(class,func) \
				STATIC ULONG _initcall_##class##func __INIT__ USED = (ULONG) class::func

#endif //__GENERIX_INIT_HPP__
