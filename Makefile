CC := gcc
CFLAGS := --warn-all --std=gnu99

.PHONY: compile clean

compile:
	$(CC) $(CFLAGS) tests/*.c src/*.c --include-directory=include --output=jsonparser

clean:
	rm jsonparser