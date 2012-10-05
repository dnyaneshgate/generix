#include <stdlib.h>

void itoa(char *buf, int base, long long d)
{
        char *p = buf;
        char *p1, *p2;
        unsigned long ud = d;

        if (base == 10 && d < 0)
        {
                *p++ = '-';
                buf++;
                ud = -d;
        }

        do
        {
                int remainder = ud % base;
                *p++ = (remainder < 10)? remainder + '0':remainder + 'a' - 10;
        } while (ud /= base);

        *p = 0;

        // reverse the string
        p1 = buf;
        p2 = p - 1;
        while (p1 < p2)
        {
                char tmp = *p1;
                *p1 = *p2;
                *p2 = tmp;
                p1++;
                p2--;
        }
}
