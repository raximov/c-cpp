#include <ncurses.h>
#include <time.h>

#include "frontend.h"

int main(int argc, char *argv[]) {
  srand(time(NULL));
  if (argc == 6) {
    start_train(argv);
  } else {
    initscr();
    noecho();
    curs_set(0);
    start_color();
    keypad(stdscr, TRUE);

    game_loop();

    endwin();
  }
  return 0;
}
