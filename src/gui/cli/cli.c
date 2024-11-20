#include "cli.h"



void initGui() {
  initscr();
  curs_set(0);
  cbreak();
  noecho();
  nodelay(stdscr, TRUE);
  scrollok(stdscr, TRUE);
}

void printGame(GameInfo game) { printField(game); }

void printField(GameInfo gameInfo) {
  mvwprintw(stdscr, 1, 10, "TETRIS");
  mvwprintw(stdscr, 3, 26, "Next figure:");
  mvwprintw(stdscr, 11, 26, "Lvl: %d", gameInfo.level);
  mvwprintw(stdscr, 13, 26, "Speed: %d", gameInfo.speed);
  mvwprintw(stdscr, 15, 26, "Score: %d", gameInfo.score);
  clrtoeol();
  mvwprintw(stdscr, 17, 26, "High score: %d", gameInfo.high_score);
  if (gameInfo.pause) mvwprintw(stdscr, 12, 2, "Press ENTER to play.");
  mvwprintw(stdscr, 24, 6, "Press:");
  mvwprintw(stdscr, 24, 14, "Start: 'Enter'");
  mvwprintw(stdscr, 25, 14, "Pause: 'p'");
  mvwprintw(stdscr, 26, 14, "Exit: 'q'");
  mvwprintw(stdscr, 27, 14, "Arrows to move: '<' '>'");
  mvwprintw(stdscr, 28, 14, "Space to rotate: '___'");
  mvwprintw(stdscr, 29, 14, "Arrow down to plant: 'v'");
}

UserAction getActions() {
  UserAction action = 0;
  char ch = getch();
  switch (ch) {
    case 'w':
      action = UP;
      break;
    case 's':
      action = DOWN;
      break;
    case 'a':
      action = LEFT;
      break;
    case 'd':
      action = RIGHT;
      break;
    case '\n':
      action = START;
      break;
    case 'p':
      action = PAUSE;
      break;
    case 'q':
      action = TERMINATE;
      break;
    default:
      action = ACTION;
      break;
  }
  return action;
}
