#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

#ifndef JSONPARSER_H
#define JSONPARSER_H

#define MAX_JSON_KEYS 100

typedef enum {
    JSON_STRING = 1,
    JSON_NUMBER,
    JSON_OBJECT,
    JSON_ARRAY,
    JSON_NULL
} jvalue_t;

typedef struct {
    char *key;
    void *value;
    jvalue_t value_type;
} json_entry_t;

typedef struct {
    unsigned int size;
    json_entry_t *entries;
} json_t;

json_t read(char *payload, unsigned long long payload_size);

#endif