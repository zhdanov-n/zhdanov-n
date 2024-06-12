CC = gcc
CFLAGS = -Wall -Wextra -Werror -Wpedantic -std=c11 -g
LDLIBS = 

SRCS = s21_cat.c cat_func.c
OBJS = $(SRCS:.c=.o)

TARGET = s21_cat

.PHONY: all clean test style rebuild

all: clean style $(TARGET) test

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LDLIBS)
	rm -f $(OBJS)
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

style:
	clang-format --style=google -i *.c *.h
test:
	sh test_func_cat.sh
	sh cat_test.sh

clean:
	rm -rf $(TARGET) $(OBJS) *.out

rebuild: clean $(TARGET)

