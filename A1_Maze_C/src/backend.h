#ifndef S21_BACKEND_H_
#define S21_BACKEND_H_

#define QTABLE_NAME "qtable.txt"

#include "maze.h"

bool load_maze(const char *filename, Maze *maze);
void load_maze_from_content(char *str, Maze *maze);
bool load_cave(const char *filename, Cave *cave);
int isValidMove(Maze *maze, int x, int y, int fromX, int fromY,
                int distance[MAX_SIZE][MAX_SIZE]);
int get_solution_bfs(Maze *maze, Point *start, Point *end, int **path);
bool isValidPoint(Maze *maze, Point *p);
point_valid areStartEndValid(Maze *maze, Point *start, Point *end);
void save_maze(const Maze *maze, const char *filename);

void initialize_q_table(float ***q_table);
int select_action(float ***q_table, int x, int y, float *eps,
                  int episode_count);
int select_best_action(float ***q_table, int x, int y);
void update_q_value(float ***q_table, int x, int y, int action, float reward,
                    int new_x, int new_y);
void find_path_with_q_table(Point *start, Point *end, int **path,
                            float ***q_table);
float calculate_reward(int visited[MAX_SIZE][MAX_SIZE], Maze *maze, int *new_x,
                       int *new_y, int *x, int *y, Point *end);
void save_q_table(const char *filename, float ***q_table);
bool load_q_table(const char *filename, float ***q_table);
void train(Point *start, Point *end, float ***q_table, Maze *maze,
           bool is_print);

Maze *create_maze();
Cave *create_cave();
void free_maze(Maze *maze);
void free_cave(Cave *cave);
int **create_path();
float ***create_q_table();
void free_q_table(float ***q_table);
void free_path(int **path);

int get_max_size();

void merge_sets(Maze *maze, int i, int cols, int rows, int *sets);
void generate_maze(Maze *maze, int rows, int cols);

void initialize_can_change(int can_change[MAX_SIZE][MAX_SIZE], int rows,
                           int cols, int initial_chance);
int count_live_neighbors(Cave *cave, int y, int x);
void update_cave(Cave *cave, int birth_limit, int death_limit,
                 int can_change[MAX_SIZE][MAX_SIZE]);

#endif
