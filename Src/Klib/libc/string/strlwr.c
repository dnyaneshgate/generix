#include <string.h>

char *strlwr(char *s) {
	char *p;

	p = s;
	while (*p) {
		if ((*p >= 'A') && (*p <= 'Z'))
			*p += 'a' - 'A';
		p++;
	};

	return s;
}
