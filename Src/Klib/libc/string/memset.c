
#include <string.h>

void* memset(void* to, int val, size_t len)
{
	char *dest = (char*)to;
	
	while(len--)
	{
		*dest++ = val;
	}
	return to;
}
