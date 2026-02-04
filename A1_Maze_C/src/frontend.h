#ifndef S21_FRONTEND_H_
#define S21_FRONTEND_H_

// #define _DEFAULT_SOURCE
#include <ncurses.h>
#include <time.h>
#include <unistd.h>

#include "backend.h"
#include "maze.h"

#define MAZE_LOAD "maze.txt"

int nanosleep(const struct timespec *req, struct timespec *rem);

void get_filename(int start_y, int start_x, char *filename);
bool get_dimension(int start_y, int start_x, int *rows, int *cols);
bool get_cave_info(int start_y, int start_x, int *birth_limit, int *death_limit,
                   int *initial_chance, int *mode, int *delay);
void game_loop();
void render_maze(int start_y, int start_x, int max_height, int max_width,
                 const Maze *maze, int **path, bool is_path);
void print_menu(int start_y, int start_x, Point *s, Point *e);
void print_load_error();
void get_start_end_points(int start_y, int start_x, Point *start, Point *end,
                          int menu_x);
void print_point_eror(point_valid v, int x, int y);
void render_ml(Point *start, Point *end, float ***q_table, Maze *maze,
               int start_x, int max_height, int max_width);
void msleep(long msec);
void start_train(char *argv[]);
void print_wrong_dimension_error();
void print_input_error();

void render_cave(int start_y, int start_x, int max_height, int max_width,
                 const Cave *cave);
void step_by_step_mode(Cave *cave, int birth_limit, int death_limit,
                       int can_change[MAX_SIZE][MAX_SIZE]);
void automatic_mode(Cave *cave, int birth_limit, int death_limit, int delay,
                    int can_change[MAX_SIZE][MAX_SIZE]);

void case_q(bool *isQuit);
void case_f(int input_start_y, int input_start_x, char *filename, Maze *maze,
            int maze_start_y, int maze_start_x, int maze_area_height,
            int maze_area_width, int **path, bool *is_loaded, bool *is_path,
            int menu_start_y, int menu_start_x, Point *start, Point *end);
void case_p(int menu_start_y, int menu_start_x, Point *start, Point *end,
            Maze *maze, int **path, bool *is_path, int maze_start_y,
            int maze_start_x, int maze_area_height, int maze_area_width);
void case_s(int input_start_y, int input_start_x, Point *start, Point *end,
            Maze *maze, int menu_start_x, int maze_start_y, int maze_start_x,
            int maze_area_height, int maze_area_width, int **path,
            bool is_path);
void case_train(Point *start, Point *end, float ***q_table, Maze *maze,
                int menu_start_x, int maze_area_height, int maze_area_width);
void case_m(int menu_start_y, int menu_start_x, Point *start, Point *end,
            Maze *maze, int **path, float ***q_table, bool *is_path,
            int maze_start_y, int maze_start_x, int maze_area_height,
            int maze_area_width);
void case_g(int input_start_y, int input_start_x, Maze *maze, Point *start,
            Point *end, int menu_start_y, int menu_start_x, int *g_rows,
            int *g_cols, bool *is_loaded, int maze_start_y, int maze_start_x,
            int maze_area_height, int maze_area_width, int **path,
            bool *is_path);
void case_c(int input_start_y, int input_start_x, char *filename, Cave *cave,
            int menu_start_y, int menu_start_x, Point *start, Point *end,
            int *birth_limit, int *death_limit, int *initial_chance, int *mode,
            int *delay, int can_change[MAX_SIZE][MAX_SIZE]);
void main_loop(bool *isQuit, bool *is_loaded, bool *is_path, char *filename,
               Maze *maze, Cave *cave, int **path, float ***q_table,
               Point *start, Point *end, int *g_rows, int *g_cols,
               int *birth_limit, int *death_limit, int *initial_chance,
               int *mode, int *delay, int can_change[MAX_SIZE][MAX_SIZE]);

#endif
