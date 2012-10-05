
#include <string.h>

void* memcpy(void* to, const void* from, size_t len)
{
	char *dest = (char*)to;
	const char *src = (char*)from;
	while(len--)
	{
		*dest++ = *src++;
	}
	return to;
}
