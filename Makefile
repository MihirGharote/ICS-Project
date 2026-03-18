CC = gcc
CFLAGS = -pedantic -Wall -Wextra -Wconversion -Wsign-conversion 

# INFO: To add new compile folders, add them below, separated by spaces
SRCDIRS = .
# INFO: Add additional libraries below, like -lm
LIBS = 

SRCS := $(foreach d,$(SRCDIRS),$(wildcard $(d)/*.c))

.PHONY: clean run

main: $(SRCS)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

clean:
	rm main

run: main
	@./main
