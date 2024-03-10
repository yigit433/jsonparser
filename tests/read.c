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

    char payload[] = "{\"a\": \"Marie Curie\", \"b\": \"Albert Einstein\"}";
    size_t payloadSize = strlen(payload);

    json_t myjson = read(payload, payloadSize);

    if (myjson.size == 0) {
        puts("✗ Read test failed, json could not be read!");

        return;
    }

    for (int i = 0; i < myjson.size; ++i) {
        printf("%s: %s\n", myjson.entries[i].key, (char*)myjson.entries[i].value);

        free(myjson.entries[i].key);
        free(myjson.entries[i].value);
        continue;
    }
    free(myjson.entries);

    puts("✓ Read test was passed successfully.");

    return;
}