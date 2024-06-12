CC = gcc
TEST_LIBS = -lcheck
ifeq ($(shell uname -s), Linux)
	TEST_LIBS += -lsubunit -lm
endif
CFLAGS = -std=c11 -Wall -Werror -Wextra -g
SOURCES = $(wildcard *.c)
OBJECTS = $(patsubst %.c, %.o, $(SOURCES))

all: test

test: clean s21_matrix.a
	$(CC) $(CFLAGS) tests/*.c s21_matrix.a -o test $(TEST_LIBS)
	./test
	rm -rf *.o tests/*.o

s21_matrix.a: $(OBJECTS)
	ar rcs s21_matrix.a $(OBJECTS)

gcov_flag:
	$(eval CFLAGS += -fprofile-arcs -ftest-coverage)

gcov_report: clean gcov_flag test
	gcov $(SOURCES)
	rm -rf test*.gcno test*.gcda test*.gcov #matrix_utils.gcno matrix_utils.gcda matrix_utils.gcov
	gcovr -s --html-details -o coverage.html
	open coverage.html
	rm -rf *.gcno *.gcda *.gcov
	
style:
	clang-format --style=google -i *.c *.h
	clang-format --style=google -i tests/*.c tests/*.h

test_leaks: s21_matrix.a
	$(CC) $(CFLAGS) tests/*.c s21_matrix.a -o test $(TEST_LIBS)
ifeq ($(shell uname -s), Linux)
	rm -rf *.o tests/*.o
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./test
else
	leaks --atExit -- ./test
endif


clean:
	rm -rf *.a *.o tests/*.o test *.gcno *.gcda *.gcov *.info coverage* *.dSYM

.PHONY: s21_matrix.a all clean test style
