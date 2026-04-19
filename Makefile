CC = gcc
CFLAGS = -Wall -Wextra

TARGET = main

# INFO: To add new compile folders, add them below, separated by spaces
SRCDIRS = . renderer choice_handling combat ascii_art minigames
# INFO: Add additional libraries below, like -lm
LIBS = -lncurses -lm

SRCS := $(foreach d,$(SRCDIRS),$(wildcard $(d)/*.c))

.PHONY: clean run

$(TARGET): $(SRCS) story2/printline.c
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

clean:
	rm $(TARGET)

run: $(TARGET)
	@./$(TARGET)
