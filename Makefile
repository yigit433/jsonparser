CC := gcc
CFLAGS := --warn-all --std=c99

.PHONY: compile clean

compile:
	$(CC) $(CFLAGS) utils/*.c tests/*.c src/*.c --include-directory=include --output=jsonparser -lm

clean:
	rm jsonparser