## Json Parser
Parses and processes JSON documents.

### Installation
1. Download the library: `git clone https://github.com/yigit433/jsonparser.git`
2. Go to the library directory: `cd jsonparser`
3. Execute the library: `gcc -o jsonparser jsonparser.c -lm`

### Example code
```c
#include <stdio.h>
#include "jsonparser.h"

int main() {
  char payload[100] = "{\"name\": \"John Doe\", \"city\": \"Istanbul\"}";
  JsonKv* output;
  size_t outputSize;

  jsonParse(payload, strlen(payload), &output, &outputSize);

  for (size_t x = 0; x < outputSize; x++) {
      JsonKv data = output[x];
      printf("[%zu.] Key: %s | Value: %s\n", x + 1, data.key, data.value);
      free(data.key);
      free(data.value);
  }

  free(output);

  return 0;
}
```