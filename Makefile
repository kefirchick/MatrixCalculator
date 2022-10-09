CC = g++
CFLAGS = -c -Wall -Werror -Wextra -std=c++17 -pedantic
TSTFLAGS = -pthread -lgtest_main -lgtest
OS = $(shell uname -s)

all: test

test: s21_matrix_oop.a s21_matrix_oop.o test.cpp
	$(CC) $(TSTFLAGS) $^
	-./a.out

s21_matrix_oop.a: s21_matrix_oop.o
	ar rcs $@ $^

s21_matrix_oop.o: s21_matrix_oop.cpp
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -rf *.o *.a *.gcda *.gcno *.info *.out report

rebuild: clean all

check: clean
	cp ../materials/linters/CPPLINT.cfg CPPLINT.cfg
	-python3 ../materials/linters/cpplint.py *.cpp
	rm CPPLINT.cfg
	cppcheck --enable=all --suppress=missingIncludeSystem --language=c++ ./*.cpp

valgrind: test
ifeq ($(OS), Darwin)
	CK_FORK=no leaks --atExit -- ./a.out
else
	valgrind --leak-check=full --show-leak-kinds=all \
        --track-origins=yes --verbose --quiet -s ./a.out 
endif

gcov_report: s21_matrix_oop.cpp test.cpp
	$(CC) $(TSTFLAGS) -fprofile-arcs -ftest-coverage $^
	-./a.out
	lcov -t "test" --no-external -o test.info -c -d .
	genhtml -o report test.info
ifeq ($(OS), Darwin)
	-open report/index.html
else
	-xdg-open report/index.html
endif

.PHONY: all clean rebuild test valgrind gcov_report