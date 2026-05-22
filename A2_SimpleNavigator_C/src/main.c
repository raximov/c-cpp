#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "s21_graph/s21_graph.h"
#include "s21_graph_algorithms/s21_graph_algorithms.h"

void print_menu() {
  printf("\n================= ГЛАВНОЕ МЕНЮ =================");
  printf("\n1. Загрузить исходный граф из файла");
  printf("\n2. Обход графа в ширину (BFS)");
  printf("\n3. Обход графа в глубину (DFS)");
  printf("\n4. Поиск кратчайшего пути между двумя вершинами (Дейкстра)");
  printf("\n5. Поиск кратчайших путей между всеми парами вершин (Флойд)");
  printf("\n6. Поиск минимального остовного дерева (Прим)");
  printf("\n7. Решение задачи коммивояжера (Муравьиный алгоритм)");
  printf("\n8. Исследование эффективности алгоритмов TSP (Бенчмарк)");
  printf("\n0. Выход из программы");
  printf("\n================================================");
  printf("\nВыберите пункт меню: ");
}

void handle_bfs(graph* g) {
  int start;
  printf("Введите стартовую вершину (от 1 до %d): ", g->vertices_count);
  if (scanf("%d", &start) != 1) return;
  int* res = breadth_first_search(g, start);
  if (res) {
    printf("Результат BFS: ");
    for (int i = 0; i < g->vertices_count; i++) printf("%d ", res[i]);
    printf("\n");
    free(res);
  } else {
    printf("Ошибка: неверная стартовая вершина!\n");
  }
}

void handle_dfs(graph* g) {
  int start;
  printf("Введите стартовую вершину (от 1 до %d): ", g->vertices_count);
  if (scanf("%d", &start) != 1) return;
  int* res = depth_first_search(g, start);
  if (res) {
    printf("Результат DFS: ");
    for (int i = 0; i < g->vertices_count; i++) printf("%d ", res[i]);
    printf("\n");
    free(res);
  } else {
    printf("Ошибка: неверная стартовая вершина!\n");
  }
}

void handle_dijkstra(graph* g) {
  int v1, v2;
  printf("Введите первую вершину: ");
  if (scanf("%d", &v1) != 1) return;
  printf("Введите вторую вершину: ");
  if (scanf("%d", &v2) != 1) return;
  int path = get_shortest_path_between_vertices(g, v1, v2);
  if (path != -1) {
    printf("Кратчайшее расстояние между %d и %d: %d\n", v1, v2, path);
  } else {
    printf("Путь между вершинами не найден или введены неверные индексы.\n");
  }
}

void handle_floyd(graph* g) {
  int** res = get_shortest_paths_between_all_vertices(g);
  if (res) {
    printf("Матрица кратчайших путей:\n");
    for (int i = 0; i < g->vertices_count; i++) {
      for (int j = 0; j < g->vertices_count; j++) {
        if (res[i][j] == INF)
          printf("INF ");
        else
          printf("%3d ", res[i][j]);
      }
      printf("\n");
      free(res[i]);
    }
    free(res);
  }
}

void handle_prim(graph* g) {
  int** mst = get_least_spanning_tree(g);
  if (mst) {
    printf("Матрица смежности минимального остовного дерева:\n");
    for (int i = 0; i < g->vertices_count; i++) {
      for (int j = 0; j < g->vertices_count; j++) {
        printf("%3d ", mst[i][j]);
      }
      printf("\n");
      free(mst[i]);
    }
    free(mst);
  }
}

void handle_tsp(graph* g) {
  tsm_result res = solve_traveling_salesman_problem(g);
  if (res.vertices) {
    printf("Кратчайший маршрут коммивояжера: %.1f\nПорядок обхода: ",
           res.distance);
    for (int i = 0; i <= g->vertices_count; i++) printf("%d ", res.vertices[i]);
    printf("\n");
    free(res.vertices);
  } else {
    printf("Решение задачи коммивояжера невозможно для данного графа.\n");
  }
}
void handle_benchmark(graph* g) {
  printf("\nЗапуск исследования эффективности для %d вершин...\n",
         g->vertices_count);
  printf("Подождите, идет расчет (особенно для Брутфорса)...\n\n");

  // Замер Муравьиного алгоритма
  clock_t start_ant = clock();
  tsm_result res_ant = solve_traveling_salesman_problem(g);
  clock_t end_ant = clock();
  double time_ant = (double)(end_ant - start_ant) / CLOCKS_PER_SEC;

  // Замер Брутфорса
  clock_t start_brute = clock();
  tsm_result res_brute = solve_traveling_salesman_brute_force(g);
  clock_t end_brute = clock();
  double time_brute = (double)(end_brute - start_brute) / CLOCKS_PER_SEC;

  // Вывод красивой таблицы результатов
  printf("-----------------------------------------------------------\n");
  printf("| Алгоритм          | Длина пути     | Время выполнения (сек) |\n");
  printf("-----------------------------------------------------------\n");
  printf("| Муравьиный (ACO)  | %14.1f | %22.6f |\n", res_ant.distance,
         time_ant);
  printf("| Полный перебор    | %14.1f | %22.6f |\n", res_brute.distance,
         time_brute);
  printf("-----------------------------------------------------------\n");

  if (res_ant.vertices) free(res_ant.vertices);
  if (res_brute.vertices) free(res_brute.vertices);
}
int main() {
  graph* g = create_graph();
  int choice = -1;
  char filename[256];

  while (choice != 0) {
    print_menu();
    if (scanf("%d", &choice) != 1) {
      printf("Ошибка ввода! Введите число.\n");
      int c;
      while ((c = getchar()) != '\n' && c != EOF);  // Очистка буфера stdin
      continue;
    }

    if (choice == 0) break;

    if (choice == 1) {
      printf("Введите путь к файлу графа: ");
      scanf("%s", filename);
      if (load_graph_from_file(g, filename)) {
        printf("Граф успешно загружен! Вершин: %d, Ориентирован: %s\n",
               g->vertices_count, g->is_oriented ? "Да" : "Нет");
      } else {
        printf("Ошибка при загрузке файла графа.\n");
      }
      continue;
    }

    // Защита: если граф еще не загружен, не пускаем к алгоритмам
    if (g->vertices_count == 0) {
      printf("Сначала необходимо загрузить граф (Пункт 1)!\n");
      continue;
    }

    switch (choice) {
      case 2:
        handle_bfs(g);
        break;
      case 3:
        handle_dfs(g);
        break;
      case 4:
        handle_dijkstra(g);
        break;
      case 5:
        handle_floyd(g);
        break;
      case 6:
        handle_prim(g);
        break;
      case 7:
        handle_tsp(g);
        break;
      case 8:
        handle_benchmark(g);
        break;
      default:
        printf("Неверный пункт меню!\n");
        break;
    }
  }

  free_graph(g);
  printf("Программа успешно завершена. Пока!\n");
  return 0;
}
