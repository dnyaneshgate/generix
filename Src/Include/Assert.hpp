#ifndef __GENERIX_ASSERT_HPP__
#define __GENERIX_ASSERT_HPP__

#include <ScreenIo.hpp>
#include <Processor/Processor.hpp>

inline static void _assert(const char *file, const int line, const char *expr) {
	CLI();
	Console::SetFontColor(Console::CYAN);
	printk("{%s:%d} Assertion \"%s\" failed", file, line, expr);
	HLT();
}

#define assert(expr) ((expr)?(void)0:_assert(__FILE__,__LINE__,#expr))
#define ASSERT(expr) assert(expr)

#endif //__GENERIX_ASSERT_HPP__
