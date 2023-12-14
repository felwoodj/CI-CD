CC=gcc
CFLAGS= -Wall -Werror -Wextra

all: s21_grep

s21_grep: s21_grep.o
	$(CC) $(CFLAGS) s21_grep.o -o s21_grep
	rm -rf *.o

s21_grep.o: s21_grep.c 
	$(CC) $(CFLAGS) -c s21_grep.c

clean: 
	rm -rf *.o *.out *.a s21_grep

style: 
	clang-format -style=google -n *.c
	clang-format -style=google -n *.h

rebuild: clean all