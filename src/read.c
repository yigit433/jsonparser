#include <json.h>

json_t read(char *payload, unsigned long long payloadSize)
{
    json_entry_t *entries = malloc(MAX_JSON_KEYS * sizeof(json_entry_t));
    json_t output;

    int keyReaded = 0;
    int valReaded = 0;

    int i = 0;

    if (payload[0] != '{' && payload[0] != '[')
    {
        output.size = 0;
        output.entries = NULL;
        return output;
    }

    while (i < payloadSize)
    {
        char *str = &payload[i];

        if (*str == '"')
        {
            int ix = i + 1;

            if (keyReaded == valReaded)
            {
                entries[keyReaded].key = malloc(1 * sizeof(char));
            }
            else
            {
                entries[valReaded].value = malloc(1 * sizeof(char));
            }

            while (payload[ix] != '"')
            {
                if (keyReaded == valReaded)
                {
                    entries[keyReaded].key = realloc(entries[keyReaded].key, (ix + 1) * sizeof(char));
                    entries[keyReaded].key[ix - i - 1] = payload[ix];

                    if (payload[ix + 1] == '"')
                        (entries)[keyReaded].key[ix - i] = '\0';
                }
                else
                {
                    entries[valReaded].value = realloc(entries[valReaded].value, (ix + 1) * sizeof(char));
                    ((char *)entries[valReaded].value)[ix - i - 1] = payload[ix];

                    if (payload[ix + 1] == '"')
                        ((char *)entries[valReaded].value)[ix - i] = '\0';

                    (entries)[valReaded].valueType = JSON_STRING;
                }
                ix++;
                continue;
            }

            if (keyReaded == valReaded)
                keyReaded++;
            else if (keyReaded > valReaded)
                valReaded++;

            i = ix;
        }

        i++;
    }

    output.entries = entries;
    output.size = keyReaded;

    return output;
}