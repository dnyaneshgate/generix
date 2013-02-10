#include <string.h>

int strlen(const char* src) {
	const char* str = src;
	if (str == 0)
		return 0;
	while (*str++)
		;
	return str - src - 1;
}
