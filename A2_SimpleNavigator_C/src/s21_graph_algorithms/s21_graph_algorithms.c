#include "s21_graph_algorithms.h"

int* depth_first_search(graph* g, int start_vertex) {
  if (!g || !g->matrix || start_vertex < 1 || start_vertex > g->vertices_count)
    return NULL;

  int n = g->vertices_count;
  int start = start_vertex - 1;

  int* visited_order = (int*)malloc(n * sizeof(int));
  bool* visited = (bool*)calloc(n, sizeof(bool));
  int order_index = 0;

  Stack* s = create_stack();
  push_stack(s, start);

  while (!is_empty_stack(s)) {
    int curr = pop_stack(s);

    if (!visited[curr]) {
      visited[curr] = true;
      visited_order[order_index++] = curr + 1;

      // Обходим соседей в обратном порядке, чтобы меньшие вершины выстреливали
      // первыми
      for (int i = n - 1; i >= 0; i--) {
        if (g->matrix[curr][i] > 0 && !visited[i]) {
          push_stack(s, i);
        }
      }
    }
  }

  free_stack(s);
  free(visited);
  return visited_order;
}

int* breadth_first_search(graph* g, int start_vertex) {
  if (!g || !g->matrix || start_vertex < 1 || start_vertex > g->vertices_count)
    return NULL;

  int n = g->vertices_count;
  int start = start_vertex - 1;

  int* visited_order = (int*)malloc(n * sizeof(int));
  bool* visited = (bool*)calloc(n, sizeof(bool));
  int order_index = 0;

  Queue* q = create_queue();
  push_queue(q, start);
  visited[start] = true;

  while (!is_empty_queue(q)) {
    int curr = pop_queue(q);
    visited_order[order_index++] = curr + 1;

    for (int i = 0; i < n; i++) {
      if (g->matrix[curr][i] > 0 && !visited[i]) {
        visited[i] = true;
        push_queue(q, i);
      }
    }
  }

  free_queue(q);
  free(visited);
  return visited_order;
}
// --- Part 2. Поиск кратчайших путей ---

// Алгоритм Дейкстры для двух вершин
int get_shortest_path_between_vertices(graph* g, int vertex1, int vertex2) {
  if (!g || !g->matrix || vertex1 < 1 || vertex1 > g->vertices_count ||
      vertex2 < 1 || vertex2 > g->vertices_count) {
    return -1;
  }

  int n = g->vertices_count;
  int start = vertex1 - 1;
  int end = vertex2 - 1;

  int* distance = (int*)malloc(n * sizeof(int));
  bool* visited = (bool*)calloc(n, sizeof(bool));

  for (int i = 0; i < n; i++) {
    distance[i] = INF;
  }
  distance[start] = 0;

  for (int i = 0; i < n - 1; i++) {
    int min_dist = INF;
    int min_index = -1;

    // Находим невыбранную вершину с минимальным расстоянием
    for (int j = 0; j < n; j++) {
      if (!visited[j] && distance[j] < min_dist) {
        min_dist = distance[j];
        min_index = j;
      }
    }

    if (min_index == -1) break;
    visited[min_index] = true;

    // Релаксация ребер
    for (int j = 0; j < n; j++) {
      if (!visited[j] && g->matrix[min_index][j] > 0 &&
          distance[min_index] != INF &&
          distance[min_index] + g->matrix[min_index][j] < distance[j]) {
        distance[j] = distance[min_index] + g->matrix[min_index][j];
      }
    }
  }

  int result = distance[end];
  free(distance);
  free(visited);

  return result == INF ? -1 : result;
}

// Алгоритм Флойда-Уоршелла для всех пар вершин
int** get_shortest_paths_between_all_vertices(graph* g) {
  if (!g || !g->matrix) return NULL;

  int n = g->vertices_count;

  // Выделяем память под результирующую матрицу
  int** res_matrix = (int**)malloc(n * sizeof(int*));
  for (int i = 0; i < n; i++) {
    res_matrix[i] = (int*)malloc(n * sizeof(int));
  }

  // Инициализация матрицы путей
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (i == j) {
        res_matrix[i][j] = 0;
      } else if (g->matrix[i][j] > 0) {
        res_matrix[i][j] = g->matrix[i][j];
      } else {
        res_matrix[i][j] = INF;
      }
    }
  }

  // Основной цикл Флойда-Уоршелла
  for (int k = 0; k < n; k++) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (res_matrix[i][k] != INF && res_matrix[k][j] != INF &&
            res_matrix[i][k] + res_matrix[k][j] < res_matrix[i][j]) {
          res_matrix[i][j] = res_matrix[i][k] + res_matrix[k][j];
        }
      }
    }
  }

  return res_matrix;
}
// --- Part 3. Поиск минимального остовного дерева (Алгоритм Прима) ---

int** get_least_spanning_tree(graph* g) {
  if (!g || !g->matrix || g->vertices_count <= 0) return NULL;

  int n = g->vertices_count;

  // Выделяем память под результирующую матрицу остова
  int** mst_matrix = (int**)malloc(n * sizeof(int*));
  for (int i = 0; i < n; i++) {
    mst_matrix[i] = (int*)calloc(n, sizeof(int));
  }

  bool* selected = (bool*)calloc(n, sizeof(bool));
  selected[0] = true;  // Начинаем с первой вершины (индекс 0)

  int edges_count = 0;

  // Остовное дерево в связном графе всегда имеет ровно n - 1 рёбер
  while (edges_count < n - 1) {
    int min_weight = INF;
    int row = -1;
    int col = -1;

    // Ищем минимальное ребро среди всех доступных переходов
    for (int i = 0; i < n; i++) {
      if (selected[i]) {
        for (int j = 0; j < n; j++) {
          if (!selected[j] && g->matrix[i][j] > 0) {
            if (g->matrix[i][j] < min_weight) {
              min_weight = g->matrix[i][j];
              row = i;
              col = j;
            }
          }
        }
      }
    }

    // Если граф связный, мы всегда найдём ребро. Если нет — прерываемся.
    if (row != -1 && col != -1) {
      mst_matrix[row][col] = min_weight;
      mst_matrix[col][row] = min_weight;  // Остов неориентированный
      selected[col] = true;
      edges_count++;
    } else {
      break;
    }
  }

  free(selected);
  return mst_matrix;
}
#include <math.h>
#include <time.h>

// --- Part 4. Задача коммивояжера (Муравьиный алгоритм) ---

tsm_result solve_traveling_salesman_problem(graph* g) {
  tsm_result result;
  result.vertices = NULL;
  result.distance = INF;

  if (!g || !g->matrix || g->vertices_count <= 0) return result;

  int n = g->vertices_count;
  srand(time(NULL));

  // Параметры алгоритма ACO
  const double ALPHA = 1.0;  // Влияние феромона
  const double BETA = 2.0;   // Влияние близости городов (видимости)
  const double RHO = 0.5;    // Коэффициент испарения феромона
  const double Q = 100.0;    // Количество оставляемого феромона
  const int ITERATIONS = 250;
  const int ANTS = n;

  // Инициализация матриц феромонов и видимости
  double** pheromone = (double**)malloc(n * sizeof(double*));
  double** visibility = (double**)malloc(n * sizeof(double*));
  for (int i = 0; i < n; i++) {
    pheromone[i] = (double*)malloc(n * sizeof(double));
    visibility[i] = (double*)malloc(n * sizeof(double));
    for (int j = 0; j < n; j++) {
      pheromone[i][j] = 1.0;  // Начальный уровень феромона
      if (i != j && g->matrix[i][j] > 0) {
        visibility[i][j] = 1.0 / (double)g->matrix[i][j];
      } else {
        visibility[i][j] = 0.0;
      }
    }
  }

  int* best_path = (int*)malloc((n + 1) * sizeof(int));
  double best_distance = INF;

  // Основной цикл итераций колонии
  for (int iter = 0; iter < ITERATIONS; iter++) {
    int** ant_paths = (int**)malloc(ANTS * sizeof(int*));
    double* ant_distances = (double*)calloc(ANTS, sizeof(double));

    for (int ant = 0; ant < ANTS; ant++) {
      ant_paths[ant] = (int*)malloc((n + 1) * sizeof(int));
      bool* visited = (bool*)calloc(n, sizeof(bool));

      // Каждый муравей стартует в своем уникальном городе
      int start_city = ant % n;
      ant_paths[ant][0] = start_city;
      visited[start_city] = true;
      int current_city = start_city;
      bool path_valid = true;

      for (int step = 1; step < n; step++) {
        double* probabilities = (double*)calloc(n, sizeof(double));
        double sum_prob = 0.0;

        for (int next_city = 0; next_city < n; next_city++) {
          if (!visited[next_city] && g->matrix[current_city][next_city] > 0) {
            probabilities[next_city] =
                pow(pheromone[current_city][next_city], ALPHA) *
                pow(visibility[current_city][next_city], BETA);
            sum_prob += probabilities[next_city];
          }
        }

        if (sum_prob == 0.0) {
          path_valid = false;
          free(probabilities);
          break;
        }

        // Выбор следующего города рулеткой
        double rand_val = (double)rand() / RAND_MAX * sum_prob;
        int next_city = -1;
        double current_sum = 0.0;
        for (int c = 0; c < n; c++) {
          if (!visited[c] && g->matrix[current_city][c] > 0) {
            current_sum += probabilities[c];
            if (current_sum >= rand_val) {
              next_city = c;
              break;
            }
          }
        }

        if (next_city == -1) next_city = current_city;  // Фоллбэк защита

        ant_paths[ant][step] = next_city;
        visited[next_city] = true;
        ant_distances[ant] += g->matrix[current_city][next_city];
        current_city = next_city;
        free(probabilities);
      }

      // Возврат в начальный город
      if (path_valid && g->matrix[current_city][start_city] > 0) {
        ant_paths[ant][n] = start_city;
        ant_distances[ant] += g->matrix[current_city][start_city];

        if (ant_distances[ant] < best_distance) {
          best_distance = ant_distances[ant];
          for (int i = 0; i <= n; i++) {
            best_path[i] = ant_paths[ant][i];
          }
        }
      } else {
        ant_distances[ant] = INF;
      }
      free(visited);
    }

    // Испарение феромонов
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        pheromone[i][j] *= (1.0 - RHO);
        if (pheromone[i][j] < 0.1)
          pheromone[i][j] = 0.1;  // Полностью не исчезает
      }
    }

    // Обновление феромонов успешными муравьями
    for (int ant = 0; ant < ANTS; ant++) {
      if (ant_distances[ant] < INF) {
        double delta_p = Q / ant_distances[ant];
        for (int step = 0; step < n; step++) {
          int from = ant_paths[ant][step];
          int to = ant_paths[ant][step + 1];
          pheromone[from][to] += delta_p;
          pheromone[to][from] += delta_p;
        }
      }
    }

    // Чистим память итерации
    for (int ant = 0; ant < ANTS; ant++) free(ant_paths[ant]);
    free(ant_paths);
    free(ant_distances);
  }

  // Освобождаем ресурсы матриц
  for (int i = 0; i < n; i++) {
    free(pheromone[i]);
    free(visibility[i]);
  }
  free(pheromone);
  free(visibility);

  if (best_distance < INF) {
    result.distance = best_distance;
    result.vertices = (int*)malloc((n + 1) * sizeof(int));
    for (int i = 0; i <= n; i++) {
      result.vertices[i] = best_path[i] + 1;  // Преобразуем в формат ТЗ (с 1)
    }
  }
  free(best_path);

  return result;
}
// --- Part 6. Исследование эффективности (Полный перебор) ---

void brute_force_recursion(graph* g, int curr, int count, double curr_dist,
                           int* path, bool* visited, int* best_path,
                           double* min_dist) {
  int n = g->vertices_count;

  if (count == n) {
    if (g->matrix[curr][path[0]] > 0) {
      double total_dist = curr_dist + g->matrix[curr][path[0]];
      if (total_dist < *min_dist) {
        *min_dist = total_dist;
        for (int i = 0; i < n; i++) best_path[i] = path[i];
        best_path[n] = path[0];
      }
    }
    return;
  }

  for (int next = 0; next < n; next++) {
    if (!visited[next] && g->matrix[curr][next] > 0) {
      visited[next] = true;
      path[count] = next;
      brute_force_recursion(g, next, count + 1,
                            curr_dist + g->matrix[curr][next], path, visited,
                            best_path, min_dist);
      visited[next] = false;
    }
  }
}

tsm_result solve_traveling_salesman_brute_force(graph* g) {
  tsm_result result;
  result.vertices = NULL;
  result.distance = INF;

  if (!g || !g->matrix || g->vertices_count <= 0) return result;

  int n = g->vertices_count;
  int* path = (int*)malloc(n * sizeof(int));
  int* best_path = (int*)malloc((n + 1) * sizeof(int));
  bool* visited = (bool*)calloc(n, sizeof(bool));

  path[0] =
      0;  // Начинаем жестко с города 0 для исключения циклических повторов
  visited[0] = true;

  double min_dist = INF;
  brute_force_recursion(g, 0, 1, 0.0, path, visited, best_path, &min_dist);

  if (min_dist < INF) {
    result.distance = min_dist;
    result.vertices = (int*)malloc((n + 1) * sizeof(int));
    for (int i = 0; i <= n; i++) result.vertices[i] = best_path[i] + 1;
  }

  free(path);
  free(best_path);
  free(visited);
  return result;
}
