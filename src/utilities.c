#include "utilities.h"
void to_string(char *buf, size_t size, unsigned long long number)
{
    memset(buf, '0', size);
    for(int i = size - 1; i >= 0; --i)
    {
        buf[i] = (number % 10)+'0';
        number /= 10;
    }
}
