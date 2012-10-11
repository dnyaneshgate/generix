#include <string.h>

char* strncpy(char* dest, const char* src, size_t n) {
	if (*src == 0 || n == 0)
		return dest;

	char* str = dest;
	while ((*str++ = *src++) && n--);
	*str = 0;
	return dest;
}
