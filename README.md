## Json Parser
Parses and processes JSON documents.

### Installation
1. Download the library: `git clone https://github.com/yigit433/jsonparser.git`
2. Go to the library directory: `cd jsonparser`
3. Execute the library: `gcc -o jsonparser jsonparser.c -lm`

### Example code
```c
#include <stdio.h>
#include <stddef.h>
#include <jsonparser.h>

int main() {
  char payload[100] = "{\"name\": \"John Doe\", \"city\": \"Istanbul\", \"age\": 20}";

  json_t* output;
  size_t outputSize;

  parse(payload, sizeof(payload), &output, &outputSize);

  printf("Output size: %lu\n", outputSize);

  for (int x = 0; x < outputSize; x++) {
    json_t data = output[x];

    printf("[%i.] Key: %s", x + 1, data.key);

    if (data.valueType == JSON_STRING) printf(" | Value: %s\n", (char*)data.value);
 
    free(data.key);
    free(data.value);
  }

  free(output);

  return 0;
}

```