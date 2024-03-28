#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>

#ifndef JSONPARSER_UTILS_H
#define JSONPARSER_UTILS_H

#define MAX_JSON_KEYS 100

int index_of(const char *str, const char target, unsigned long long str_length);
double custom_atof(const char *str, unsigned long long str_length);

#endif