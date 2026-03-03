CC=gcc
CFLAGS=-Wall -Werror -Wextra
TEST_CFLAGS=-fprofile-arcs -ftest-coverage
SRC_DIR=.
TEST_DIR=tests
COVERAGE_DIR=coverage_report


SRCS=$(wildcard $(SRC_DIR)/s21*.c) $(wildcard $(SRC_DIR)/other_func/*.c)
OBJS=$(SRCS:.c=.o)

TEST_SRCS=$(wildcard $(TEST_DIR)/*.c)
TEST_OBJS=$(TEST_SRCS:.c=.o)

# Определение команды для открытия файлов в зависимости от ОС
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
    TEST_LIBS=-lcheck -lm -lpthread -lrt -lsubunit
    OPEN_CMD=xdg-open
else ifeq ($(UNAME_S),Darwin)
    TEST_LIBS=-lcheck -lm
    OPEN_CMD=open
endif

all: s21_math.a

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

s21_math.a: $(OBJS)
	ar rcs $@ $^

test: $(TEST_OBJS) s21_math.a
	$(CC) $(CFLAGS) $(TEST_OBJS) -L. ./s21_math.a $(TEST_LIBS) -o test.out $(TEST_CFLAGS)
	./test.out

gcov_report:
	rm -rf $(COVERAGE_DIR)
	mkdir $(COVERAGE_DIR)
	$(CC) $(CFLAGS) --coverage $(SRCS) $(TEST_SRCS) -o test.out $(TEST_LIBS) $(TEST_CFLAGS)
	./test.out
	lcov -t 'test' -o $(COVERAGE_DIR)/test.info -c -d .
	genhtml -o $(COVERAGE_DIR) $(COVERAGE_DIR)/test.info
	$(OPEN_CMD) $(COVERAGE_DIR)/src/index.html

view_coverage:
	$(OPEN_CMD) $(COVERAGE_DIR)/index.html
format:
	cp ../materials/linters/.clang-format ./
	find . -type f -regex ".*\.\(c\|h\)" -exec clang-format -i -style=file {} \;
	rm -rf .clang-format

clean:
	find . -type f \( -name "*.o" -o -name "*.a" -o -name "*.out" -o -name "*.gcda" -o -name "*.gcno" -o -name "*.css" -o -name "*.html" \) -exec rm -v {} +
	rm -rf $(COVERAGE_DIR)