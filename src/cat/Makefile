CC=gcc
CFLAGS= -Wall -Werror -Wextra

all: s21_cat

s21_cat: s21_cat.o
	$(CC) $(CFLAGS) s21_cat.o -o s21_cat
	rm -rf *.o

s21_cat.o: s21_cat.c
	$(CC) $(CFLAGS) -c s21_cat.c

clean:
	rm -rf *.o *.out *.a s21_cat

style:
	clang-format -style=google -n *.c
	clang-format -style=google -n *.h

rebuild: clean all