CC = gcc
CFLAGS = -pedantic -Wall -Wextra -Wconversion -Wsign-conversion 

TARGET = main

# INFO: To add new compile folders, add them below, separated by spaces
SRCDIRS = . renderer choice_handling
# INFO: Add additional libraries below, like -lm
LIBS = -lncurses

SRCS := $(foreach d,$(SRCDIRS),$(wildcard $(d)/*.c))

.PHONY: clean run

$(TARGET): $(SRCS) story2/printline.c
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

clean:
	rm $(TARGET)

run: $(TARGET)
	@./$(TARGET)
