
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
