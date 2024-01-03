#include <jsonparser.h>

void parse(char *payload, size_t payload_size, json_t **output, size_t *output_size) {
  *output = malloc(MAX_JSON_KEYS * sizeof(json_t));

  int keyReaded = 0;
  int valReaded = 0;
  int i = 0;

  while (i < payload_size) {
    char str = payload[i];

    if (str == '"') {
      int ix = i + 1;

      if (keyReaded == valReaded) {
        (*output)[keyReaded].key = malloc(1 * sizeof(char));
      } else if (keyReaded > valReaded) {
        (*output)[valReaded].value = malloc(1 * sizeof(char));
      }

      while (payload[ix] != '"') {
        if (keyReaded == valReaded) {
          (*output)[keyReaded].key = realloc((*output)[keyReaded].key, (ix + 1) * sizeof(char));
          (*output)[keyReaded].key[ix - i - 1] = payload[ix];

          if (payload[ix + 1] == '"')
            (*output)[keyReaded].key[ix - i] = 0;
        } else if (keyReaded > valReaded) {
          (*output)[valReaded].value = realloc((*output)[valReaded].value, (ix + 1) * sizeof(char));

          ((char *)(*output)[valReaded].value)[ix - i - 1] = payload[ix];

          if (payload[ix + 1] == '"')
            ((char *)(*output)[valReaded].value)[ix - i] = '\0';

          (*output)[valReaded].valueType = JSON_STRING;
        }

        ix++;
      }

      if (keyReaded == valReaded)
        keyReaded++;
      else if (keyReaded > valReaded)
        valReaded++;

      i = ix;
    } else if (atof(&str) != 0 || (atof(&str) == 0 && str == '0')) { 
      int ix = i + 1;
      int condition = 1;

      char *data = malloc(1*sizeof(char));

      data[0] = str;

      while (condition == 1) {
        char elem = payload[ix];

        if (elem == '}' || elem == ',' || elem == ']' || elem == '}') {
          condition = 0;

          data[ix - i] = '\0';
        } else {
          data[ix - i] = elem;
        }

        ix++;
      }

      (*output)[keyReaded - 1].value = data;
      (*output)[keyReaded - 1].valueType = JSON_NUMBER;

      valReaded++;
      i = ix;
    } 

    i++;
  }

  *output_size = keyReaded;
}