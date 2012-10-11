#include <string.h>

char* strcpy(char* dest, const char* src) {
	if (*src == 0)
		return dest;

	char* str = dest;
	while ((*str++ = *src++));
	*str = 0;
	return dest;
}
