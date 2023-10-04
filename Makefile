CC=g++
CFLAGS=-c -Wall -Werror -Wextra -std=c++17
FLAGS=-Wall -Werror -Wextra -std=c++17
SOURCE=$(wildcard s21_*.cpp)
OBJECTS=$(patsubst %.cpp,%.o, ${SOURCE})

all: clean s21_matrix_oop.a test

s21_matrix_oop.a: s21_matrix_oop.cpp
	@$(CC) $(CFLAGS) s21_matrix_oop.cpp
	@ar rc $@ $(OBJECTS)
	@ranlib $@

main: main.cpp s21_matrix_oop.a
	@$(CC) $(FLAGS) -o main.out $^
	@./main.out

clean:
	@rm -rf *.a *.o *.out
