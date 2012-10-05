#include <string.h>

char* strchr(const char* dest, int c) {

	const char* str1 = dest;
	char cc = c;
	while (*str1) {
		if (*str1 == cc)
			return (char*) str1;
		str1++;
	}

	return 0;
}
