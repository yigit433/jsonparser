#include <json.h>

json_t read(char *payload, unsigned long long payload_size)
{
    json_entry_t *entries = malloc(MAX_JSON_KEYS * sizeof(json_entry_t));
    json_t output;

    int keyReaded = 0;
    int valReaded = 0;

    int i = 0;

    if (payload[0] != '{' && payload[0] != '[')
    {
        free(entries);
        output.error = 1;
        output.size = 0;
        output.entries = NULL;

        return output;
    }

    while (i < payload_size)
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

                    (entries)[valReaded].value_type = JSON_STRING;
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
        else if (custom_atof(str, 1) != 0 || (custom_atof(str, 1) == 0 && *str == '0'))
        {
            char *readed = malloc(1 * sizeof(char));

            int ix = i;
            int condition = 1;

            while (condition == 1)
            {
                if ((payload[ix] != ',' && payload[ix] != '}' && payload[ix] != ']') == 1)
                {
                    readed = realloc(readed, (ix - i + 1) * sizeof(char));
                    readed[ix - i] = payload[ix];
                }  else {
                    readed[ix - i + 1] = '\0';
                    condition = 0;
                }

                ix++;
                continue;
            }
            i = ix;
            
            (entries)[valReaded].value = malloc(1 * sizeof(double));
            *(double *)(entries)[valReaded].value = custom_atof(readed, strlen(readed));

            (entries)[valReaded].value_type = JSON_NUMBER;

            free(readed);
        }

        i++;
    }

    output.entries = entries;
    output.size = keyReaded;

    return output;
}