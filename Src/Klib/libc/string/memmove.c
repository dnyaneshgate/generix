
#include <string.h>

void* memmove(void *to, const void* from, size_t len) {
	char *dest = (char*) to;
	const char *src = (char*) from;
	if (dest < src) {
		memcpy(dest, src, len);
	} else {
		dest += len;
		src += len;
		while (len--) {
			*dest-- = *src--;
		}
	}
	return to;
}

void* memmove_b(void *to, const void* from, size_t len) {
	char *dest = (char*) to;
	const char *src = (char*) from;
	if (dest < src) {
		memcpy(dest, src, len);
	} else {
		dest += len;
		src += len;
		while (len--) {
			*dest-- = *src--;
		}
	}
	return to;
}

void* memmove_w(void *to, const void* from, size_t len) {
	short *dest = (short*) to;
	const short *src = (short*) from;
	if (dest < src) {
		memcpy(dest, src, len);
	} else {
		dest += len;
		src += len;
		while (len--) {
			*dest-- = *src--;
		}
	}
	return to;
}

void* memmove_l(void *to, const void* from, size_t len) {
	int *dest = (int*) to;
	const int *src = (int*) from;
	if (dest < src) {
		memcpy(dest, src, len);
	} else {
		dest += len;
		src += len;
		while (len--) {
			*dest-- = *src--;
		}
	}
	return to;
}
