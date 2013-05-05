#include <string.h>

void * memset(void* to, char val, size_t len) {
	char *dest = (char*) to;

	while (len--)
		*dest++ = val;

	return to;
}

void * memset_b(void* to, char val, size_t len) {
	char *dest = (char*) to;

	while (len--)
		*dest++ = val;

	return to;
}

void * memset_w(void* to, short val, size_t len) {
	short *dest = (short*) to;

	while (len--)
		*dest++ = val;

	return to;
}

void * memset_l(void* to, int val, size_t len) {
	int *dest = (int*) to;

	while (len--)
		*dest++ = val;

	return to;
}
