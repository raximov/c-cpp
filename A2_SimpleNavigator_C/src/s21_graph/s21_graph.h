#ifndef S21_GRAPH_H
#define S21_GRAPH_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct graph {
  int vertices_count;
  int** matrix;
  bool is_oriented;
} graph;

// Создание пустого графа
graph* create_graph();
// Очистка памяти графа
void free_graph(graph* g);
// Загрузка графа из файла (возвращает true, если успешно)
bool load_graph_from_file(graph* g, char* filename);
// Экспорт графа в формат DOT
void export_graph_to_dot(graph* g, char* filename);

#endif  // S21_GRAPH_H
