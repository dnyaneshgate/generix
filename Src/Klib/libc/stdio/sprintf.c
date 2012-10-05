/*
 * sprintf.c
 *
 *  Created on: Sep 30, 2012
 *      Author: dnyanesh
 */
#include <stdio.h>
#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif

extern int vsprintf(char * buf, const char * fmt, va_list args);

int sprintf(char *buff,const char *format,...){
	int i = 0;
	va_list args;
	va_start(args,format);
	i = vsprintf(buff,format,args);
	va_end(args);
	return i;
}

#ifdef __cplusplus
}
#endif
