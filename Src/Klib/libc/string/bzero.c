
#include <string.h>

void bzero(void *dest,size_t n){
	if(n){
		memset(dest,'\0',n);
	}
}
