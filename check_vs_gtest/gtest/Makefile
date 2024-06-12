CC = g++
TEST_LIBS = -lgtest -lgtest_main
ifeq ($(shell uname -s), Linux)
	TEST_LIBS += -lsubunit -lm -pthread
endif
CFLAGS = -std=c++17 -Wall -Werror -Wextra -g
SOURCES = $(wildcard *.cpp)
OBJECTS = $(patsubst %.cpp, %.o, $(SOURCES))

all: check_style test

test: clean s21_matrix_oop.a
	$(CC) $(CFLAGS) tests/*.cpp s21_matrix_oop.a -o test $(TEST_LIBS)
	./test
	rm -rf *.o tests/*.o

s21_matrix_oop.a: 
	$(CC) $(CFLAGS) -c $(SOURCES)
	ar rcs s21_matrix_oop.a $(OBJECTS)

gcov_flag:
	$(eval CFLAGS += -fprofile-arcs -ftest-coverage)

gcov_report: clean gcov_flag test
	gcov $(SOURCES)
	rm -rf test*.gc*
	gcovr --exclude-noncode-lines --exclude-unreachable-branches --exclude-branches-by-pattern '.*throw.*|.*delete.*|.*Free.*|.*Gaussian.*|.*this != &other.*|.*Submatrix.*|.*Cofactor.*|.*Inverse.*|.*double det = Determinant().*' -s --html-details -o coverage.html
	open coverage.html
	rm -rf *.gc*
	
style:
	clang-format --style=google -i *.cpp *.h
	clang-format --style=google -i tests/*.cpp

check_style:
	clang-format --style=google -n *.cpp *.h
	clang-format --style=google -n tests/*.cpp

test_leaks: s21_matrix_oop.a
	$(CC) $(CFLAGS) tests/*.cpp s21_matrix_oop.a -o test $(TEST_LIBS)
ifeq ($(shell uname -s), Linux)
	rm -rf *.o tests/*.o
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./test
else
	leaks --atExit -- ./test
endif


clean:
	rm -rf *.a *.o tests/*.o test *.gcno *.gcda *.gcov *.info coverage* *.dSYM

.PHONY: s21_matrix_oop.a all clean test style
