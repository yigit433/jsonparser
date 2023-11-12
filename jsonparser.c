#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_JSON_KEYS 100

typedef struct {
    char* key;
    char* value;
} JsonKv;

void jsonParse(char* payload, size_t payloadSize, JsonKv** output, size_t* outputSize) {
    JsonKv* payloadLoaded = malloc(MAX_JSON_KEYS * sizeof(JsonKv));

    int i = 0;
    int readedKey = 0;
    int readedValue = 0;

    while (i < payloadSize) {
        if (payload[i] == '"') {
            int j = i + 1;
            int k = 0;
            char* value = malloc(1 * sizeof(char));

            while (payload[j] != '"') {
                value[k] = payload[j];
                value = realloc(value, (k + 2) * sizeof(char));
                j++;
                k++;
            }

            value[k] = '\0';

            if (readedKey == readedValue) {
                payloadLoaded[readedKey].key = strdup(value);
            }
            else if (readedKey > readedValue) {
                payloadLoaded[readedValue].value = strdup(value);
                readedValue++;
            }

            free(value);

            i = j;
        }
        else if (payload[i] == ':') {
            readedKey++;
        }

        i++;
        continue;
    }

    *output = payloadLoaded;
    *outputSize = readedValue;
}