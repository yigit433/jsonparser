#include <stdlib.h>
#include <stdio.h>
#include <json.h>

void test_read();

int main() {
    // Running the read test
    test_read();

    return 0;
}

void test_read() {
    puts("#1 Starting the reading test..");

    char payload[] = "{\"name\": \"Marie Curie\", \"country\": \"Poland\", \"age\": 67}";
    unsigned long long payloadSize = strlen(payload);

    json_t myjson = read(payload, payloadSize);

    if (myjson.size == 0 && myjson.error == 1) {
        puts("✗ Read test failed, json could not be read!");

        return;
    }

    for (int i = 0; i < myjson.size; ++i) {
        json_entry_t entry = myjson.entries[i];
        
        printf("%s: ", myjson.entries[i].key);

        if (entry.value_type == JSON_STRING) {
            printf("%s\n", (char*)myjson.entries[i].value);
        } else if (entry.value_type == JSON_NUMBER) {
            printf("%f\n", *(double*)myjson.entries[i].value);
        }

        free(myjson.entries[i].key);
        free(myjson.entries[i].value);
        continue;
    }
    free(myjson.entries);

    puts("✓ Read test was passed successfully.");

    return;
}