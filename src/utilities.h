#ifndef UTIL
#define UTIL
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <limits.h>
void to_string(char *buf, size_t size, unsigned long long number);

char getb(FILE * stream);
#endif