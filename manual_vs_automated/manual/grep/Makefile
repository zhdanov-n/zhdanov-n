CC = gcc
CFLAGS = -Wall -Wextra -Werror -Wpedantic -std=c11 -g
LDLIBS =

SRCS = s21_grep.c grep_func.c
OBJS = $(SRCS:.c=.o)

TARGET = s21_grep

.PHONY: all clean test style rebuild

all: clean style $(TARGET) test

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LDLIBS)
	rm -f $(OBJS)
%.o: %.c
	gcc $(CFLAGS) -c $< -o $@

style:
	clang-format --style=google -i *.c *.h
test:
	sh s21_grep_test.sh
	sh s21_grep_test_p2p.sh

clean:
	rm -rf $(TARGET) $(OBJS) *.out

rebuild: clean $(TARGET)

