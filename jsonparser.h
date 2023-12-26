#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

#ifndef JSONPARSER_H
#define JSONPARSER_H

#define MAX_JSON_KEYS 100  

typedef enum
{
    JSON_STRING = 1,
    JSON_NUMBER,
    JSON_OBJECT,
    JSON_ARRAY,
    JSON_NULL
} jvalue_t;

typedef struct
{
    char *key;
    void *value;
    jvalue_t valueType;
} json_t;

void parse(char *payload, size_t payload_size, json_t **output, size_t* output_size);

#endif
