/* -*- Mode: C++; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * cpp-kernel
 * Copyright (C) Dnyanesh Gate 2012 <dnyanesh@localhost.localdomain>
 * 
 */

#include <stdio.h>
#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif

	static char buf[1024];
	extern int vsprintf(char * buf, const char * fmt, va_list args);

	int printf(const char *format, ...) {
		int i = 0;
		va_list args;
		va_start(args, format);
		i = vsprintf(buf, format, args);
		va_end(args);
		//puts(buf);
		return i;
	}

#ifdef __cplusplus
}
#endif
