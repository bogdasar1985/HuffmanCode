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

//https://github.com/thedeg123/bitio/blob/master/bitio.c
//Эта функция не работает, как надо
char getb(FILE * stream)
{
    static char c;
    static int pos = 0;
    #ifdef DEBUG
    fprintf(stdout, "Func getb(): pos = %d\n", pos);
    #endif
    if(pos > 0 && c != EOF)
    {
        pos--;
        return ((c >> pos) &1)? '1':'0';
    }
    else
    {
        pos = CHAR_BIT;
        c = getc(stream);
        return (c != EOF) ? getb(stream) : EOF;
    }
}