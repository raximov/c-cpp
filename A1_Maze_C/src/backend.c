#include "backend.h"

#include <time.h>

#include "maze.h"

#define LIVE 1  // talking about cells in caves
#define DEAD 0

Maze *create_maze() {
  Maze *maze = calloc(1, sizeof(Maze));
  maze->rows = 0;
  maze->cols = 0;
  memset(maze->vertical_walls, 0, sizeof(maze->vertical_walls));
  memset(maze->horizontal_walls, 0, sizeof(maze->horizontal_walls));
  return maze;
}

int **create_path() {
  int **path = calloc(MAX_SIZE, sizeof(int *));
  for (int i = 0; i < MAX_SIZE; ++i) {
    path[i] = calloc(MAX_SIZE, sizeof(int));
  }
  return path;
}

float ***create_q_table() {
  float ***q_table = calloc(MAX_SIZE, sizeof(float **));
  for (int i = 0; i < MAX_SIZE; i++) {
    q_table[i] = calloc(MAX_SIZE, sizeof(float *));
    for (int j = 0; j < MAX_SIZE; ++j) {
      q_table[i][j] = calloc(ACTIONS_COUNT, sizeof(float));
    }
  }
  return q_table;
}

void free_q_table(float ***q_table) {
  for (int i = 0; i < MAX_SIZE; i++) {
    for (int j = 0; j < MAX_SIZE; ++j) {
      free(q_table[i][j]);
    }
    free(q_table[i]);
  }
  free(q_table);
}

void free_path(int **path) {
  for (int i = 0; i < MAX_SIZE; ++i) {
    free(path[i]);
  }
  free(path);
}

void free_maze(Maze *maze) { free(maze); }

bool load_maze(const char *filename, Maze *maze) {
  bool isLoad = 0;
  FILE *file = fopen(filename, "r");
  if (file != NULL) {
    fscanf(file, "%d %d", &maze->rows, &maze->cols);
    for (int i = 0; i < maze->rows; ++i) {
      for (int j = 0; j < maze->cols; ++j) {
        fscanf(file, "%d", &maze->vertical_walls[i][j]);
      }
    }
    for (int i = 0; i < maze->rows; ++i) {
      for (int j = 0; j < maze->cols; ++j) {
        fscanf(file, "%d", &maze->horizontal_walls[i][j]);
      }
    }
    fclose(file);
    isLoad = 1;
  }
  return isLoad;
}

void load_maze_from_content(char *str, Maze *maze) {
  char *ptr = str;
  int read = 0;
  sscanf(ptr, "%d %d%n", &maze->rows, &maze->cols, &read);
  ptr += read;
  for (int i = 0; i < maze->rows; ++i) {
    for (int j = 0; j < maze->cols; ++j) {
      sscanf(ptr, "%d%n", &maze->vertical_walls[i][j], &read);
      ptr += read;
    }
  }
  for (int i = 0; i < maze->rows; ++i) {
    for (int j = 0; j < maze->cols; ++j) {
      sscanf(ptr, "%d%n", &maze->horizontal_walls[i][j], &read);
      ptr += read;
    }
  }
}

int isValidMove(Maze *maze, int x, int y, int fromX, int fromY,
                int distance[MAX_SIZE][MAX_SIZE]) {
  int ret = MOVE_INVALID;
  if (x < 0 || x >= maze->rows || y < 0 || y >= maze->cols)
    ret = MOVE_OUT;
  else if (distance != NULL && distance[x][y] != NO_PATH)
    ret = MOVE_INVALID;
  else if (x == fromX && y == fromY + 1)
    ret = maze->vertical_walls[fromX][fromY] ? MOVE_INVALID : MOVE_VALID;
  else if (x == fromX && y == fromY - 1)
    ret = maze->vertical_walls[fromX][fromY - 1] ? MOVE_INVALID : MOVE_VALID;
  else if (x == fromX + 1 && y == fromY)
    ret = maze->horizontal_walls[fromX][fromY] ? MOVE_INVALID : MOVE_VALID;
  else if (x == fromX - 1 && y == fromY)
    ret = maze->horizontal_walls[fromX - 1][fromY] ? MOVE_INVALID : MOVE_VALID;
  return ret;
}

int get_solution_bfs(Maze *maze, Point *start, Point *end, int **path) {
  int dirX[4] = {-1, 1, 0, 0};
  int dirY[4] = {0, 0, -1, 1};
  int distance[MAX_SIZE][MAX_SIZE];
  Point prev[MAX_SIZE][MAX_SIZE];
  Point queue[MAX_SIZE * MAX_SIZE];
  int front = 0, rear = 0;
  for (int i = 0; i < maze->rows; i++) {
    for (int j = 0; j < maze->cols; j++) {
      distance[i][j] = NO_PATH;
      if (path != NULL) path[i][j] = 0;
      prev[i][j].x = -1;
      prev[i][j].y = -1;
    }
  }
  queue[rear++] = *start;
  distance[start->x][start->y] = 0;
  while (front < rear) {
    Point current = queue[front++];
    if (current.x == end->x && current.y == end->y) break;
    for (int i = 0; i < 4; i++) {
      int newX = current.x + dirX[i];
      int newY = current.y + dirY[i];
      if (isValidMove(maze, newX, newY, current.x, current.y, distance) ==
          MOVE_VALID) {
        distance[newX][newY] = distance[current.x][current.y] + 1;
        queue[rear++] = (Point){newX, newY};
        prev[newX][newY].x = current.x;
        prev[newX][newY].y = current.y;
      }
    }
  }
  if (path != NULL && distance[end->x][end->y] != NO_PATH) {
    Point current = *end;
    while (current.x != start->x || current.y != start->y) {
      path[current.x][current.y] = 1;
      int prevX = prev[current.x][current.y].x;
      int prevY = prev[current.x][current.y].y;
      current = (Point){prevX, prevY};
    }
    path[start->x][start->y] = 1;
  }
  return distance[end->x][end->y];
}

bool isValidPoint(Maze *maze, Point *p) {
  bool ret = true;
  if (p->x < 0 || p->x >= maze->rows || p->y < 0 || p->y >= maze->cols) {
    ret = false;
  }
  return ret;
}

point_valid areStartEndValid(Maze *maze, Point *start, Point *end) {
  point_valid ret = VALID;
  if (!isValidPoint(maze, start)) {
    printf("Start point is invalid.\n");
    ret = INVALID_START;
  } else if (!isValidPoint(maze, end)) {
    printf("End point is invalid.\n");
    ret = INVALID_END;
  }

  return ret;
}

// ML
void initialize_q_table(float ***q_table) {
  if (!load_q_table(QTABLE_NAME, q_table)) {
    for (int i = 0; i < MAX_SIZE; ++i) {
      for (int j = 0; j < MAX_SIZE; ++j) {
        for (int action = 0; action < ACTIONS_COUNT; ++action) {
          q_table[i][j][action] = 0.0f;
        }
      }
    }
  }
}

int select_action(float ***q_table, int x, int y, float *eps,
                  int episode_count) {
  int ret = 0;
  *eps = MAX_EPS -
         (MAX_EPS - MIN_EPS) * (1 - exp(-DECAY_RATE * (float)episode_count));
  *eps = fmaxf(*eps, MIN_EPS);
  if ((float)rand() / (float)RAND_MAX < *eps) {
    ret = rand() % ACTIONS_COUNT;
  } else {
    ret = select_best_action(q_table, x, y);
  }
  return ret;
}

int select_best_action(float ***q_table, int x, int y) {
  float max_q_value = q_table[x][y][0];
  int best_action = 0;
  for (int action = 1; action < ACTIONS_COUNT; ++action) {
    if (q_table[x][y][action] > max_q_value) {
      max_q_value = q_table[x][y][action];
      best_action = action;
    }
  }
  return best_action;
}

void update_q_value(float ***q_table, int x, int y, int action, float reward,
                    int new_x, int new_y) {
  float max_future_q = q_table[new_x][new_y][0];
  for (int next_action = 1; next_action < ACTIONS_COUNT; ++next_action) {
    if (q_table[new_x][new_y][next_action] > max_future_q) {
      max_future_q = q_table[new_x][new_y][next_action];
    }
  }
  q_table[x][y][action] +=
      ALPHA * (reward + GAMMA * max_future_q - q_table[x][y][action]);
}

void find_path_with_q_table(Point *start, Point *end, int **path,
                            float ***q_table) {
  for (int i = 0; i < MAX_SIZE; ++i) {
    for (int j = 0; j < MAX_SIZE; ++j) {
      path[i][j] = 0;
    }
  }
  if (start->x != end->x || start->y != end->y) {
    int dirX[4] = {-1, 1, 0, 0};
    int dirY[4] = {0, 0, -1, 1};
    int x = start->x;
    int y = start->y;
    int count = 0;
    while (1) {
      int best_action = select_best_action(q_table, x, y);
      path[x][y] = 1;
      x += dirX[best_action];
      y += dirY[best_action];
      if ((x == end->x && y == end->y) || (count++) > MAX_SIZE * MAX_SIZE)
        break;
    }
    path[end->x][end->y] = 1;
  }
}

float calculate_reward(int visited[MAX_SIZE][MAX_SIZE], Maze *maze, int *new_x,
                       int *new_y, int *x, int *y, Point *end) {
  float reward = 0.0f;
  int r = isValidMove(maze, *new_x, *new_y, *x, *y, NULL);
  if (r == MOVE_VALID) {
    if (*new_x == end->x && *new_y == end->y) {
      reward = 100.0f;
      *x = *new_x;
      *y = *new_y;
    } else {
      // reward += (visited[*new_x][*new_y] == 0) ? 10.0f : 0.0f;
      Point s = {.x = *x, .y = *y};
      Point s2 = {.x = *new_x, *new_y};
      int old_distance = get_solution_bfs(maze, &s, end, NULL);
      int new_distance = get_solution_bfs(maze, &s2, end, NULL);
      reward += (old_distance - new_distance) * 0.5f;
      *x = *new_x;
      *y = *new_y;
    }
  } else {
    *new_x = *x;
    *new_y = *y;
    reward += -100.0f;
  }
  ++visited[*x][*y];
  return reward;
}

void save_q_table(const char *filename, float ***q_table) {
  FILE *file = fopen(filename, "w");
  if (file != NULL) {
    for (int i = 0; i < MAX_SIZE; i++) {
      for (int j = 0; j < MAX_SIZE; j++) {
        for (int k = 0; k < ACTIONS_COUNT; k++) {
          fprintf(file, "%.6f ", q_table[i][j][k]);
        }
        fprintf(file, "\n");
      }
      fprintf(file, "\n");
    }
    fclose(file);
  }
}

void save_maze(const Maze *maze, const char *filename) {
  FILE *file = fopen(filename, "w");
  if (file != NULL) {
    fprintf(file, "%d %d\n", maze->rows, maze->cols);

    for (int i = 0; i < maze->rows; ++i) {
      for (int j = 0; j < maze->cols; ++j) {
        fprintf(file, "%d ", maze->vertical_walls[i][j]);
      }
      fprintf(file, "\n");
    }
    fprintf(file, "\n");
    for (int i = 0; i < maze->rows; ++i) {
      for (int j = 0; j < maze->cols; ++j) {
        fprintf(file, "%d ", maze->horizontal_walls[i][j]);
      }
      fprintf(file, "\n");
    }
    fclose(file);
  }
}

bool load_q_table(const char *filename, float ***q_table) {
  bool ret = false;
  FILE *file = fopen(filename, "r");
  if (file != NULL) {
    for (int i = 0; i < MAX_SIZE; i++) {
      for (int j = 0; j < MAX_SIZE; j++) {
        for (int k = 0; k < ACTIONS_COUNT; k++) {
          fscanf(file, "%f", &q_table[i][j][k]);
        }
        fscanf(file, "\n");
      }
      fscanf(file, "\n");
    }
    fclose(file);
    ret = true;
  }
  return ret;
}

void train(Point *start, Point *end, float ***q_table, Maze *maze, bool print) {
  initialize_q_table(q_table);
  int dirX[4] = {-1, 1, 0, 0};
  int dirY[4] = {0, 0, -1, 1};
  int visited[MAX_SIZE][MAX_SIZE] = {0};
  float eps = MAX_EPS;
  for (int i = 0; i < TRAIN_COUNT; ++i) {
    if (print) printf("%d / %d\n", i, TRAIN_COUNT);
    int x = start->x;
    int y = start->y;
    memset(visited, 0, sizeof(visited));
    int step = 0;
    while (1) {
      int action = select_action(q_table, x, y, &eps, i);
      int new_x = x + dirX[action];
      int new_y = y + dirY[action];
      float reward =
          calculate_reward(visited, maze, &new_x, &new_y, &x, &y, end);
      update_q_value(q_table, x, y, action, reward, new_x, new_y);
      ++step;
      if ((x == end->x && y == end->y)) break;
    }
  }
  if (print) save_q_table(QTABLE_NAME, q_table);
}

int get_max_size() { return MAX_SIZE; }

// Part 2. Generate perfect maze

void merge_sets(Maze *maze, int i, int cols, int rows, int *sets) {
  int old_set;
  for (int j = 0; j < cols - 1; ++j) {  // merging sets randomly
    if (sets[j] != sets[j + 1] && (rand() % 2 == 0 || i == rows - 1)) {
      maze->vertical_walls[i][j] = 0;
      old_set = sets[j + 1];
      for (int k = 0; k < cols; ++k) {
        if (sets[k] == old_set) {
          sets[k] = sets[j];
        }
      }
    } else {
      maze->vertical_walls[i][j] = 1;
    }
  }
}

void generate_maze(Maze *maze, int rows, int cols) {
  maze->rows = rows;
  maze->cols = cols;

  int sets[MAX_SIZE];
  int next_set = 0;  // set number
  srand(time(NULL));
  for (int j = 0; j < cols; ++j) {  // assigning set number
    sets[j] = next_set++;
  }

  for (int i = 0; i < rows; ++i) {  // generating maze each row at once
    merge_sets(maze, i, cols, rows, sets);
    bool set_connected[MAX_SIZE * MAX_SIZE] = {0};
    for (int j = 0; j < cols; ++j) {
      if (i == rows - 1) {
        maze->horizontal_walls[i][j] = 1;  // building horizontal border
      } else if (rand() % 2 == 0 ||
                 !set_connected[sets[j]]) {  // each set needs a bottom path
        maze->horizontal_walls[i][j] = 0;
        set_connected[sets[j]] = true;
      } else {
        maze->horizontal_walls[i][j] = 1;
      }
    }
    for (int j = 0; j < cols; ++j) {  // numerating new sets...
      if (maze->horizontal_walls[i][j] == 1 && i < rows - 1) {
        sets[j] = next_set++;
      }

      if (j == cols - 1)
        maze->vertical_walls[i][j] = 1;  // ...and building vertical border
    }
  }
}

// Part 4. Cave generation

Cave *create_cave() {
  Cave *cave = calloc(1, sizeof(Cave));
  cave->rows = 0;
  cave->cols = 0;
  memset(cave->cells, 0, sizeof(cave->cells));
  return cave;
}

void free_cave(Cave *cave) { free(cave); }

bool load_cave(const char *filename, Cave *cave) {
  bool isLoad = 0;
  FILE *file = fopen(filename, "r");
  if (file != NULL) {
    fscanf(file, "%d %d", &cave->rows, &cave->cols);
    for (int i = 0; i < cave->rows; ++i) {
      for (int j = 0; j < cave->cols; ++j) {
        fscanf(file, "%d", &cave->cells[i][j]);
      }
    }
    fclose(file);
    isLoad = 1;
  }
  return isLoad;
}

void initialize_can_change(int can_change[MAX_SIZE][MAX_SIZE], int rows,
                           int cols, int initial_chance) {
  srand(time(NULL));
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      int random_value = rand() % 100;
      if (random_value < initial_chance) {
        can_change[i][j] = 1;  // can change
      } else {
        can_change[i][j] = 0;  // cant change
      }
    }
  }
}

int count_live_neighbors(Cave *cave, int y, int x) {
  int count = 0, ny, nx;
  int directions[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1},
                          {0, 1},   {1, -1}, {1, 0},  {1, 1}};
  for (int i = 0; i < 8; i++) {
    ny = y + directions[i][0];
    nx = x + directions[i][1];
    if (ny >= 0 && ny < cave->rows && nx >= 0 && nx < cave->cols) {
      if (cave->cells[ny][nx] == LIVE) {
        count++;
      }
    } else {
      count++;  // counting cells outside the cave
    }
  }
  return count;
}

void update_cave(Cave *cave, int birth_limit, int death_limit,
                 int can_change[MAX_SIZE][MAX_SIZE]) {
  int new_cells[MAX_SIZE][MAX_SIZE];
  int live_neighbors = 0;
  for (int i = 0; i < cave->rows; i++) {
    for (int j = 0; j < cave->cols; j++) {
      new_cells[i][j] = cave->cells[i][j];
    }
  }

  for (int i = 0; i < cave->rows; i++) {
    for (int j = 0; j < cave->cols; j++) {
      live_neighbors = count_live_neighbors(cave, i, j);
      if (cave->cells[i][j] == LIVE && live_neighbors < death_limit &&
          can_change[i][j]) {
        new_cells[i][j] = DEAD;
      } else if (cave->cells[i][j] == DEAD && live_neighbors > birth_limit &&
                 can_change[i][j]) {
        new_cells[i][j] = LIVE;
      }
    }
  }

  for (int i = 0; i < cave->rows; i++) {
    for (int j = 0; j < cave->cols; j++) {
      cave->cells[i][j] = new_cells[i][j];
    }
  }
}
