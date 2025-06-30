TEST_FLAGS = -lcheck -pthread -lrt -lm -lsubunit -W
CC = gcc
TARGET?=s21_string.a
TEST_TARGET?=s21_string_test.a

SRCS=$(wildcard s21_*.c)
TEST_SRCS=$(wildcard tests/*.c)
TEST_OBJ = $(TEST_SRCS:.c=.o)
OBJS=$(SRCS:.c=.o)

TEST_COMPILE = $(CC) -std=c11 -g  tests/*.c -o test $(TEST_FLAGS) -L. $(TARGET) 
GCOVFLAGS = -L. -ls21_string --coverage -Wall -Wextra -Werror

$(TARGET): $(OBJS)
	ar rc $(TARGET) $(OBJS)
	rm -rf *.o
	ranlib $(TARGET)

$(TEST_TARGET): 
	cp $(TARGET) $(TEST_TARGET)

test: $(TARGET) $(TEST_TARGET)
	$(TEST_COMPILE)
	./test

gcov_report: $(TARGET) test
	rm -f *.g*
	cp s21_string.a libs21_string.a
	$(CC) -std=c11 -g *.c tests/*.c libs21_string.a $(TEST_FLAGS) $(GCOVFLAGS)
	./a.out
	lcov -t a.out -o rep.info -c -d .
	genhtml -o report rep.info
#open report/index.html
	rm -rf *.gcda *.gcno s21_tests s21_tests.info

clang:
	cp ../materials/linters/.clang-format ./.clang-format
	clang-format -n --style=Google *.c *.h tests/*.c tests/*.h
	rm -rf .clang-format

make_clang:
	cp ../materials/linters/.clang-format ./.clang-format
	clang-format -i --style=Google *.c *.h tests/*.c
	rm -rf .clang-format

all: clean s21_string.a

clean:
	rm -rf *.o *.g* *.info *.out report *.a *.dSYM debug ./test