#include <string.h>

char* strrchr(const char* dest, int c) {

	const char* str1 = dest;
	char cc = c;
	char *pos = (char*) 0;
	while (*str1) {
		if (*str1 == cc)
			pos = (char*) str1;
		str1++;
	}
	if (cc == 0)
		pos = (char*) str1;
	return (char*) pos;
}
