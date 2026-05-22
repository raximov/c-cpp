#include "s21_graph.h"

graph* create_graph() {
  graph* g = (graph*)malloc(sizeof(graph));
  if (g) {
    g->vertices_count = 0;
    g->matrix = NULL;
    g->is_oriented = false;
  }
  return g;
}

void free_graph(graph* g) {
  if (!g) return;
  if (g->matrix) {
    for (int i = 0; i < g->vertices_count; i++) {
      free(g->matrix[i]);
    }
    free(g->matrix);
  }
  free(g);
}

bool load_graph_from_file(graph* g, char* filename) {
  FILE* file = fopen(filename, "r");
  if (!file) return false;

  int size = 0;
  if (fscanf(file, "%d", &size) != 1 || size <= 0) {
    fclose(file);
    return false;
  }

  // Если в графе уже была матрица, сначала бережно чистим её
  if (g->matrix) {
    for (int i = 0; i < g->vertices_count; i++) {
      free(g->matrix[i]);
    }
    free(g->matrix);
  }

  g->vertices_count = size;
  g->matrix = (int**)malloc(size * sizeof(int*));
  for (int i = 0; i < size; i++) {
    g->matrix[i] = (int*)calloc(size, sizeof(int));
  }

  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      if (fscanf(file, "%d", &g->matrix[i][j]) != 1) {
        fclose(file);
        return false;
      }
    }
  }

  // Проверяем граф на ориентированность (ищем асимметрию)
  g->is_oriented = false;
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      if (g->matrix[i][j] != g->matrix[j][i]) {
        g->is_oriented = true;
        break;
      }
    }
    if (g->is_oriented) break;
  }

  fclose(file);
  return true;
}

void export_graph_to_dot(graph* g, char* filename) {
  if (!g || !g->matrix) return;
  FILE* file = fopen(filename, "w");
  if (!file) return;

  if (g->is_oriented) {
    fprintf(file, "digraph G {\n");
    for (int i = 0; i < g->vertices_count; i++) {
      for (int j = 0; j < g->vertices_count; j++) {
        if (g->matrix[i][j] > 0) {
          fprintf(file, "  %d -> %d [label=\"%d\"];\n", i + 1, j + 1,
                  g->matrix[i][j]);
        }
      }
    }
  } else {
    fprintf(file, "graph G {\n");
    for (int i = 0; i < g->vertices_count; i++) {
      for (int j = i; j < g->vertices_count; j++) {
        if (g->matrix[i][j] > 0) {
          fprintf(file, "  %d -- %d [label=\"%d\"];\n", i + 1, j + 1,
                  g->matrix[i][j]);
        }
      }
    }
  }
  fprintf(file, "}\n");
  fclose(file);
}
