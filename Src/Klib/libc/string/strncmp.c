#include <string.h>

int strncmp(const char* s1, const char* s2, size_t n) {
	if (n == 0)
		return 0;
	while ((*s1 == *s2) && n--) {
		if (*s1 == 0)
			return 0;
		s1++;
		s2++;
	}
	return n == 0 ? 0 : *(unsigned const char*) s1 - *(unsigned const char*) s2;
}
