#include <string.h>

char* strncat(char* dest, const char* src, size_t n){
	if(*src == 0 || n == 0)
	return dest;
	
	char* str = dest;
	while(*str++) ;str--;
	while((*str++ = *src++) && n--) ;
	*str = 0;
	return dest;
}
