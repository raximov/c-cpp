CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11
AR = ar rcs
LDFLAGS = -lm

# Пути к исходникам
GRAPH_DIR = s21_graph
ALGO_DIR = s21_graph_algorithms

# Списки объектов
GRAPH_OBJS = $(GRAPH_DIR)/s21_graph.o
ALGO_OBJS = $(ALGO_DIR)/s21_containers.o $(ALGO_DIR)/s21_graph_algorithms.o

# Названия статических библиотек
GRAPH_LIB = s21_graph.a
ALGO_LIB = s21_graph_algorithms.a

.PHONY: all s21_graph s21_graph_algorithms clean test clang_check main

all: s21_graph s21_graph_algorithms main

# Сборка исполняемого приложения (Бонусная часть)
main: s21_graph s21_graph_algorithms main.o
	$(CC) $(CFLAGS) main.o $(GRAPH_LIB) $(ALGO_LIB) $(LDFLAGS) -o SimpleNavigator
	rm -f main.o

# Сборка статической библиотеки ядра графа
s21_graph: $(GRAPH_OBJS)
	$(AR) $(GRAPH_LIB) $(GRAPH_OBJS)

# Сборка статической библиотеки алгоритмов
s21_graph_algorithms: $(ALGO_OBJS)
	$(AR) $(ALGO_LIB) $(ALGO_OBJS)

# Компиляция отдельных файлов .c в .o объектов
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Цель очистки проекта
clean:
	rm -f $(GRAPH_DIR)/*.o $(ALGO_DIR)/*.o main.o
	rm -f $(GRAPH_LIB) $(ALGO_LIB)
	rm -f SimpleNavigator test_run
	rm -f output.dot

# Интеграционный тест
test: s21_graph s21_graph_algorithms
	echo '#include <stdio.h>' > test_main.c
	echo '#include "$(GRAPH_DIR)/s21_graph.h"' >> test_main.c
	echo '#include "$(ALGO_DIR)/s21_graph_algorithms.h"' >> test_main.c
	echo 'int main() { graph* g = create_graph(); if (load_graph_from_file(g, "matrix_test.txt")) { tsm_result res = solve_traveling_salesman_problem(g); printf("TSP Done! Dist: %.1f\\n", res.distance); if(res.vertices) free(res.vertices); } free_graph(g); return 0; }' >> test_main.c
	$(CC) $(CFLAGS) test_main.c $(GRAPH_LIB) $(ALGO_LIB) $(LDFLAGS) -o test_run
	rm test_main.c
	./test_run

# Проверка стиля кода
clang_check:
	clang-format -n *.c $(GRAPH_DIR)/*.c $(GRAPH_DIR)/*.h $(ALGO_DIR)/*.c $(ALGO_DIR)/*.h
