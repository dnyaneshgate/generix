#include <string.h>

char* strcat(char* dest, const char* src) {
	if (*src == 0)
		return dest;

	char* str = dest;
	while (*str++);
	str--;
	while ((*str++ = *src++));
	*str = 0;
	return dest;
}
