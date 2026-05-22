#ifndef S21_GRAPH_ALGORITHMS_H
#define S21_GRAPH_ALGORITHMS_H

#include "../s21_graph/s21_graph.h"
#include "s21_containers.h"

#define INF 1000000000

typedef struct tsm_result {
  int* vertices;
  double distance;
} tsm_result;

// Part 1
int* depth_first_search(graph* graph, int start_vertex);
int* breadth_first_search(graph* graph, int start_vertex);

// Part 2
int get_shortest_path_between_vertices(graph* graph, int vertex1, int vertex2);
int** get_shortest_paths_between_all_vertices(graph* graph);

// Part 3
int** get_least_spanning_tree(graph* graph);

// Part 4
tsm_result solve_traveling_salesman_problem(graph* graph);

// Part 6
tsm_result solve_traveling_salesman_brute_force(graph* graph);

#endif  // S21_GRAPH_ALGORITHMS_H
