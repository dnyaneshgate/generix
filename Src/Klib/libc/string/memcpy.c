#include <string.h>

void* memcpy(void* to, const void* from, size_t len) {
	char *dest = (char*) to;
	const char *src = (char*) from;
	while (len--) {
		*dest++ = *src++;
	}
	return to;
}

void* memcpy_b(void* to, const void* from, size_t len) {
	char *dest = (char*) to;
	const char *src = (char*) from;
	while (len--) {
		*dest++ = *src++;
	}
	return to;
}

void* memcpy_w(void* to, const void* from, size_t len) {
	short *dest = (short*) to;
	const short *src = (short*) from;
	while (len--) {
		*dest++ = *src++;
	}
	return to;
}

void* memcpy_l(void* to, const void* from, size_t len) {
	int *dest = (int*) to;
	const int *src = (int*) from;
	while (len--) {
		*dest++ = *src++;
	}
	return to;
}
