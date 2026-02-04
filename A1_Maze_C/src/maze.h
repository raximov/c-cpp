#ifndef S21_MAZE_H_
#define S21_MAZE_H_

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 50

typedef struct {
  int rows;
  int cols;
  int cells[MAX_SIZE][MAX_SIZE];
} Cave;

typedef struct {
  int rows;
  int cols;
  int vertical_walls[MAX_SIZE][MAX_SIZE];
  int horizontal_walls[MAX_SIZE][MAX_SIZE];
} Maze;

enum path { NO_PATH = -9999 };

typedef struct {
  int x, y;
} Point;

#define MAX_EPS 1.0f
#define MIN_EPS 0.01f
#define DECAY_RATE 0.0001f
#define ALPHA 0.1f
#define GAMMA 0.9f
#define TRAIN_COUNT 200

typedef enum { VALID, INVALID_START, INVALID_END } point_valid;

typedef enum { UP, DOWN, LEFT, RIGHT, ACTIONS_COUNT } actions;

typedef enum { MOVE_VALID, MOVE_INVALID, MOVE_OUT } valid_move;

#endif
