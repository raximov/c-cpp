#include "frontend.h"

#include "backend.h"
#include "maze.h"

void get_filename(int start_y, int start_x, char *filename) {
  mvprintw(start_y + 5, start_x, "Enter the filename: ");
  refresh();
  echo();
  mvgetstr(start_y + 6, start_x, filename);
  noecho();
  clear();
}

void get_start_end_points(int start_y, int start_x, Point *start, Point *end,
                          int menu_x) {
  char input[100];
  mvprintw(start_y + 5, start_x, "%s", "Input start point:");
  refresh();
  echo();
  mvgetstr(start_y + 6, start_x, input);
  sscanf(input, "%3d %3d", &start->x, &start->y);
  input[0] = '\0';
  mvprintw(start_y + 7, start_x, "%s", "Input end point:");
  mvgetstr(start_y + 8, start_x, input);
  sscanf(input, "%3d %3d", &end->x, &end->y);
  clear();
  print_menu(0, menu_x, start, end);
  noecho();
}

bool get_dimension(int start_y, int start_x, int *rows, int *cols) {
  bool isGot = 1;
  echo();
  mvprintw(start_y + 5, start_x, "Enter maze rows (1-50): ");
  refresh();
  scanw("%d", rows);
  mvprintw(start_y + 6, start_x, "Enter maze cols (1-50): ");
  refresh();
  scanw("%d", cols);
  noecho();

  if (*rows < 1 || *rows > 50 || *cols < 1 || *cols > 50) {
    *rows = 0;
    *cols = 0;
    isGot = 0;
  }
  return isGot;
}

bool get_cave_info(int start_y, int start_x, int *birth_limit, int *death_limit,
                   int *initial_chance, int *mode, int *delay) {
  bool isGot = 1;
  echo();
  mvprintw(start_y + 5, start_x, "Enter \"birth\" limit (0-7): ");
  refresh();
  scanw("%d", birth_limit);
  mvprintw(start_y + 6, start_x, "Enter \"death\" limit (0-7): ");
  refresh();
  scanw("%d", death_limit);
  mvprintw(start_y + 7, start_x, "Enter initial chance (0-100): ");
  refresh();
  scanw("%d", initial_chance);
  mvprintw(start_y + 8, start_x,
           "Select mode (0 for step-by-step, 1 for automatic): ");
  refresh();
  scanw("%d", mode);
  if (*mode) {
    mvprintw(start_y + 9, start_x, "Enter delay in milliseconds: ");
    refresh();
    scanw("%d", delay);
  }
  noecho();

  if (*birth_limit < 0 || *birth_limit > 7 || *death_limit < 0 ||
      *death_limit > 7 || *initial_chance < 0 || *initial_chance > 100 ||
      (*mode != 0 && *mode != 1) || (*mode && *delay < 0)) {
    *birth_limit = -1;
    *death_limit = -1;
    *initial_chance = -1;
    *mode = -1;
    isGot = 0;
  }
  return isGot;
}

void step_by_step_mode(Cave *cave, int birth_limit, int death_limit,
                       int can_change[MAX_SIZE][MAX_SIZE]) {
  bool isDone = 0;
  int ch;
  while (!isDone) {
    render_cave(0, 0, getmaxy(stdscr) - 2, (getmaxx(stdscr) * 2 / 3) - 1, cave);
    ch = getch();
    if (ch == 'n') {
      update_cave(cave, birth_limit, death_limit, can_change);
    } else if (ch == 'q') {
      isDone = 1;
    }
  }
}

void automatic_mode(Cave *cave, int birth_limit, int death_limit, int delay,
                    int can_change[MAX_SIZE][MAX_SIZE]) {
  int ch;
  bool isDone = 0;
  nodelay(stdscr, TRUE);
  while (!isDone) {
    update_cave(cave, birth_limit, death_limit, can_change);
    render_cave(0, 0, getmaxy(stdscr) - 2, (getmaxx(stdscr) * 2 / 3) - 1, cave);
    usleep(delay * 1000);
    ch = getch();
    if (ch == 'q') isDone = 1;
  }
  nodelay(stdscr, FALSE);
}

void case_q(bool *isQuit) { *isQuit = true; }

void case_f(int input_start_y, int input_start_x, char *filename, Maze *maze,
            int maze_start_y, int maze_start_x, int maze_area_height,
            int maze_area_width, int **path, bool *is_loaded, bool *is_path,
            int menu_start_y, int menu_start_x, Point *start, Point *end) {
  get_filename(input_start_y, input_start_x, filename);
  if ((*is_loaded = load_maze(filename, maze))) {
    *start = (Point){0, 0};
    *end = (Point){0, 0};
    *is_path = false;
    render_maze(maze_start_y, maze_start_x, maze_area_height, maze_area_width,
                maze, path, *is_path);
  } else {
    print_load_error();
  }
  print_menu(menu_start_y, menu_start_x, start, end);
}

void case_p(int menu_start_y, int menu_start_x, Point *start, Point *end,
            Maze *maze, int **path, bool *is_path, int maze_start_y,
            int maze_start_x, int maze_area_height, int maze_area_width) {
  clear();
  print_menu(menu_start_y, menu_start_x, start, end);
  *is_path = !(*is_path);
  get_solution_bfs(maze, start, end, path);
  render_maze(maze_start_y, maze_start_x, maze_area_height, maze_area_width,
              maze, path, *is_path);
}

void case_s(int input_start_y, int input_start_x, Point *start, Point *end,
            Maze *maze, int menu_start_x, int maze_start_y, int maze_start_x,
            int maze_area_height, int maze_area_width, int **path,
            bool is_path) {
  get_start_end_points(input_start_y, input_start_x, start, end, menu_start_x);
  point_valid v = areStartEndValid(maze, start, end);
  if (v != VALID) {
    print_point_eror(v, menu_start_x, input_start_y + 1);
  }
  render_maze(maze_start_y, maze_start_x, maze_area_height, maze_area_width,
              maze, path, is_path);
}

void case_train(Point *start, Point *end, float ***q_table, Maze *maze,
                int menu_start_x, int maze_area_height, int maze_area_width) {
  render_ml(start, end, q_table, maze, menu_start_x, maze_area_height,
            maze_area_width);
}

void case_m(int menu_start_y, int menu_start_x, Point *start, Point *end,
            Maze *maze, int **path, float ***q_table, bool *is_path,
            int maze_start_y, int maze_start_x, int maze_area_height,
            int maze_area_width) {
  clear();
  print_menu(menu_start_y, menu_start_x, start, end);
  *is_path = !(*is_path);
  find_path_with_q_table(start, end, path, q_table);
  render_maze(maze_start_y, maze_start_x, maze_area_height, maze_area_width,
              maze, path, *is_path);
}

void case_g(int input_start_y, int input_start_x, Maze *maze, Point *start,
            Point *end, int menu_start_y, int menu_start_x, int *g_rows,
            int *g_cols, bool *is_loaded, int maze_start_y, int maze_start_x,
            int maze_area_height, int maze_area_width, int **path,
            bool *is_path) {
  *g_rows = 0;
  *g_cols = 0;
  bool isGotDim = get_dimension(input_start_y, input_start_x, g_rows, g_cols);
  clear();
  print_menu(menu_start_y, menu_start_x, start, end);
  if (isGotDim) {
    generate_maze(maze, *g_rows, *g_cols);
    *is_path = false;
    render_maze(maze_start_y, maze_start_x, maze_area_height, maze_area_width,
                maze, path, *is_path);
    save_maze(maze, MAZE_LOAD);
    *is_loaded = true;
  } else {
    print_wrong_dimension_error();
  }
}

void case_c(int input_start_y, int input_start_x, char *filename, Cave *cave,
            int menu_start_y, int menu_start_x, Point *start, Point *end,
            int *birth_limit, int *death_limit, int *initial_chance, int *mode,
            int *delay, int can_change[MAX_SIZE][MAX_SIZE]) {
  get_filename(input_start_y, input_start_x, filename);
  clear();
  print_menu(menu_start_y, menu_start_x, start, end);
  if (load_cave(filename, cave)) {
    if (get_cave_info(input_start_y, input_start_x, birth_limit, death_limit,
                      initial_chance, mode, delay)) {
      initialize_can_change(can_change, cave->rows, cave->cols,
                            *initial_chance);
      if (!(*mode)) {
        step_by_step_mode(cave, *birth_limit, *death_limit, can_change);
      } else {
        automatic_mode(cave, *birth_limit, *death_limit, *delay, can_change);
      }
      clear();
      print_menu(menu_start_y, menu_start_x, start, end);
    } else {
      clear();
      print_input_error();
      print_menu(menu_start_y, menu_start_x, start, end);
    }
  } else {
    print_load_error();
  }
}

void main_loop(bool *isQuit, bool *is_loaded, bool *is_path, char *filename,
               Maze *maze, Cave *cave, int **path, float ***q_table,
               Point *start, Point *end, int *g_rows, int *g_cols,
               int *birth_limit, int *death_limit, int *initial_chance,
               int *mode, int *delay, int can_change[MAX_SIZE][MAX_SIZE]) {
  int term_height, term_width, maze_start_y = 0, maze_start_x = 1, menu_start_x,
                               menu_start_y = 0, input_start_x, input_start_y,
                               maze_area_height, maze_area_width, ch;

  while (!(*isQuit)) {
    getmaxyx(stdscr, term_height, term_width);
    maze_area_height = term_height - 2;
    maze_area_width = (term_width * 2 / 3) - 1;
    menu_start_x = term_width * 2 / 3 + 2;
    input_start_y = menu_start_y + 10;
    input_start_x = menu_start_x;
    print_menu(menu_start_y, menu_start_x, start, end);

    ch = getch();
    if (ch == 'q')
      case_q(isQuit);
    else if (ch == 'f')
      case_f(input_start_y, input_start_x, filename, maze, maze_start_y,
             maze_start_x, maze_area_height, maze_area_width, path, is_loaded,
             is_path, menu_start_y, menu_start_x, start, end);
    else if (ch == 'p' && *is_loaded)
      case_p(menu_start_y, menu_start_x, start, end, maze, path, is_path,
             maze_start_y, maze_start_x, maze_area_height, maze_area_width);
    else if (ch == 's' && *is_loaded)
      case_s(input_start_y, input_start_x, start, end, maze, menu_start_x,
             maze_start_y, maze_start_x, maze_area_height, maze_area_width,
             path, *is_path);
    else if (ch == 't' && *is_loaded)
      case_train(start, end, q_table, maze, menu_start_x, maze_area_height,
                 maze_area_width);
    else if (ch == 'm' && *is_loaded)
      case_m(menu_start_y, menu_start_x, start, end, maze, path, q_table,
             is_path, maze_start_y, maze_start_x, maze_area_height,
             maze_area_width);
    else if (ch == 'g')
      case_g(input_start_y, input_start_x, maze, start, end, menu_start_y,
             menu_start_x, g_rows, g_cols, is_loaded, maze_start_y,
             maze_start_x, maze_area_height, maze_area_width, path, is_path);
    else if (ch == 'c')
      case_c(input_start_y, input_start_x, filename, cave, menu_start_y,
             menu_start_x, start, end, birth_limit, death_limit, initial_chance,
             mode, delay, can_change);
  }
}

void game_loop() {
  Maze *maze = create_maze();
  Cave *cave = create_cave();
  char filename[256];

  int g_rows, g_cols;
  int birth_limit, death_limit, initial_chance, mode, delay;
  int can_change[MAX_SIZE][MAX_SIZE];

  bool isQuit = false;
  int **path = create_path();
  float ***q_table = create_q_table();
  Point start = {0, 0}, end = {0, 0};
  bool is_loaded = false, is_path = false;
  init_pair(1, COLOR_RED, COLOR_BLACK);
  initialize_q_table(q_table);

  main_loop(&isQuit, &is_loaded, &is_path, filename, maze, cave, path, q_table,
            &start, &end, &g_rows, &g_cols, &birth_limit, &death_limit,
            &initial_chance, &mode, &delay, can_change);

  free_maze(maze);
  free_cave(cave);
  free_q_table(q_table);
  free_path(path);
}

void render_cave(int start_y, int start_x, int max_height, int max_width,
                 const Cave *cave) {
  int cell_height = max_height / cave->rows;
  int cell_width = max_width / cave->cols;
  int x, y;
  char ch;

  for (int i = 0; i < cave->rows; ++i) {
    for (int j = 0; j < cave->cols; ++j) {
      y = start_y + i * cell_height;
      x = start_x + j * cell_width;
      if (cave->cells[i][j])
        ch = '#';
      else
        ch = ' ';

      for (int dy = 0; dy < cell_height; ++dy) {
        for (int dx = 0; dx < cell_width; ++dx) {
          mvaddch(y + dy, x + dx, ch);
        }
      }
    }
  }
  refresh();
}

void render_maze(int start_y, int start_x, int max_height, int max_width,
                 const Maze *maze, int **path, bool is_path) {
  int cell_height = max_height / maze->rows;
  int cell_width = max_width / maze->cols;
  // if(cell_height < 2)
  //   cell_height = 2;
  int x, y;

  mvhline(start_y, start_x, '_', max_width);
  mvvline(start_y + 1, start_x, '|', max_height);

  for (int i = 0; i < maze->rows; ++i) {
    for (int j = 0; j < maze->cols; ++j) {
      y = start_y + i * cell_height;
      x = start_x + j * cell_width;
      if (is_path && path[i][j]) {
        attron(COLOR_PAIR(1));
        if (i > 0 && path[i - 1][j] && !maze->horizontal_walls[i - 1][j])
          mvvline(y - cell_height / 2, x + cell_width / 2, '|', cell_height);
        if (j > 0 && path[i][j - 1] && !maze->vertical_walls[i][j - 1])
          mvhline(y + cell_height / 2, x - cell_width / 2, '-', cell_width + 1);
        attroff(COLOR_PAIR(1));
      }
      if (maze->horizontal_walls[i][j]) {
        mvhline(y + cell_height, x + 1, '_', cell_width);
      }

      if (maze->vertical_walls[i][j]) {
        for (int k = 1; k <= cell_height; ++k) {
          mvprintw(y + k, x + cell_width, "|");
        }
      }
    }
  }
}

void print_menu(int start_y, int start_x, Point *s, Point *e) {
  mvprintw(start_y, start_x, "f [load maze from file]");
  mvprintw(start_y + 1, start_x, "g [generate maze]");
  mvprintw(start_y + 2, start_x, "q [quit]");
  mvprintw(start_y + 3, start_x, "p [show path]");
  mvprintw(start_y + 4, start_x, "s [input start and end (if loaded)]");
  mvprintw(start_y + 5, start_x, "start: %d %d", s->x, s->y);
  mvprintw(start_y + 6, start_x, "end: %d %d", e->x, e->y);
  mvprintw(start_y + 7, start_x, "t [train model]");
  mvprintw(start_y + 8, start_x, "m [show ml path]");
  mvprintw(start_y + 9, start_x, "c [load cave from file]");
  mvprintw(start_y + 10, start_x + 2, "n [next step]");
  mvprintw(start_y + 11, start_x + 2, "q [quit step-by-step mode]");
}

void print_point_eror(point_valid v, int x, int y) {
  if (v == INVALID_START) mvprintw(y, x, "Invalid start");
  if (v == INVALID_END) mvprintw(y, x, "Invalid end");
}

void render_ml(Point *start, Point *end, float ***q_table, Maze *maze,
               int start_x, int max_height, int max_width) {
  int cell_height = max_height / maze->rows;
  int cell_width = max_width / maze->cols;
  int dirX[4] = {-1, 1, 0, 0};
  int dirY[4] = {0, 0, -1, 1};
  int visited[MAX_SIZE][MAX_SIZE] = {0};
  for (int i = 0; i < TRAIN_COUNT; ++i) {
    int x = start->x;
    int y = start->y;
    memset(visited, 0, sizeof(visited));
    int step = 0;
    float eps = MAX_EPS;
    while (1) {
      int action = select_action(q_table, x, y, &eps, i);
      int new_x = x + dirX[action];
      int new_y = y + dirY[action];
      float reward =
          calculate_reward(visited, maze, &new_x, &new_y, &x, &y, end);
      update_q_value(q_table, x, y, action, reward, new_x, new_y);
      if (x == end->x && y == end->y) break;
      if (i % 10 == 0 && step % 5 == 0) {
        int y_ = 1 + x * cell_height + cell_height / 2;
        int x_ = 1 + y * cell_width + cell_width / 2;
        clear();
        attron(COLOR_PAIR(1));
        mvprintw(y_, x_, "*");
        attroff(COLOR_PAIR(1));
        print_menu(0, start_x, start, end);
        render_maze(0, 1, max_height, max_width, maze, NULL, false);
        mvprintw(13, start_x, "%d / %d", i, TRAIN_COUNT);
        mvprintw(14, start_x, "%d %d", x, y);
        refresh();
        msleep(50);
      }
      ++step;
    }
  }
  clear();
  print_menu(0, start_x, start, end);
  save_q_table(QTABLE_NAME, q_table);
}

void msleep(long msec) {
  struct timespec ts;
  ts.tv_sec = msec / 1000;
  ts.tv_nsec = (msec % 1000) * 1000000;
  nanosleep(&ts, &ts);
}

void start_train(char *argv[]) {
  const char *filename = argv[1];
  int x1 = atoi(argv[2]);
  int y1 = atoi(argv[3]);
  int x2 = atoi(argv[4]);
  int y2 = atoi(argv[5]);
  Point start = {x1, y1}, end = {x2, y2};
  Maze *maze = create_maze();
  float ***q_table = create_q_table();
  if (load_maze(filename, maze) && isValidPoint(maze, &start) &&
      isValidPoint(maze, &end)) {
    train(&start, &end, q_table, maze, true);
  } else {
    printf("Invalid file or points");
  }
  free_maze(maze);
  free_q_table(q_table);
}

void print_load_error() { mvprintw(0, 0, "Could not load file"); }

void print_wrong_dimension_error() {
  mvprintw(0, 0, "Incorrected dimension entered");
}

void print_input_error() { mvprintw(0, 0, "Incorrect input"); }
