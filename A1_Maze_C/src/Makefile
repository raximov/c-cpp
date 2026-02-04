CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11 -fprofile-arcs -ftest-coverage
LIBS = -lncurses -lm
CHECK_LIBS = -lcheck -lpthread -lrt -lsubunit -lm
GCOV_FLAGS = --branch-counts --branch-probabilities --preserve-paths

SRCS = maze.c backend.c frontend.c
TEST_SRCS = tests.c backend.c
TARGET = maze
TEST_TARGET = test_maze

all: clean tests install run

install: $(TARGET)
	mv $(TARGET) ../out/

uninstall:
	rm -f ../out/$(TARGET)

$(TARGET): $(SRCS)
	@$(CC) $(SRCS) -o $(TARGET) $(LIBS)

run: install
	@../out/$(TARGET)

tests: clean $(TEST_SRCS)
	@$(CC) $(CFLAGS) $(TEST_SRCS) -o $(TEST_TARGET) $(CHECK_LIBS)
	@./$(TEST_TARGET)

gcov_report: tests
	@lcov --capture --directory . --output-file coverage.info --no-external
	@genhtml coverage.info --output-directory coverage_report
	@xdg-open ./coverage_report/index.html

valgrind: tests
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(TEST_TARGET)

format:
	@clang-format -i *.c *.h -style=Google

clean:
	@rm -f $(TARGET) $(TEST_TARGET) *.gcno *.gcda *.gcov coverage.info
	@rm -rf coverage_report

web:
	./web/build.sh
	./web/run.sh

.PHONY: web
