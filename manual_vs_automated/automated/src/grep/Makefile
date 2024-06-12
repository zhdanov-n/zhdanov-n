CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11 -g
LDLIBS =

SRCS = s21_grep.c grep_func.c
OBJS = $(SRCS:.c=.o)

TARGET = s21_grep

.PHONY: all clean test style rebuild

all: clean $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LDLIBS)
	rm -f $(OBJS)
%.o: %.c
	gcc $(CFLAGS) -c $< -o $@

check_style:
	clang-format --style=google -n *.c *.h

test:
	./grep_test.sh

clean:
	rm -rf $(TARGET) $(OBJS) *.out

rebuild: clean $(TARGET)

