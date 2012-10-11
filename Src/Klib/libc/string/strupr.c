#include <string.h>

char *strupr(char *s) {
	char *p;

	p = s;
	while (*p) {
		if ((*p >= 'a') && (*p <= 'z'))
			*p -= 'a' - 'A';
		p++;
	};

	return s;
}
