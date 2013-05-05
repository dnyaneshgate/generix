#include <string.h>

void bzero(void *dest, size_t n) {
	if (n) {
		char * to = (char*) dest;
		while (n--)
			*to++ = 0;
	}
}
