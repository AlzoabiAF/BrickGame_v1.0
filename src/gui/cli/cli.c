#include "cli.h"



void initGui() {
  initscr();
  curs_set(0);
  start_color();
  init_color(10, 500, 500, 500);
  init_pair(1, COLOR_BLACK, 10);
  init_pair(2, COLOR_GREEN, COLOR_GREEN);
  init_pair(3, COLOR_GREEN, COLOR_BLACK);
  init_pair(4, 10, COLOR_BLACK);
  cbreak();
  noecho();
  nodelay(stdscr, TRUE);
  scrollok(stdscr, TRUE);
}



void printGame(Game *game, struct timespec sp_start,
               struct timespec sp_end) {
  printField(game);
  printFigure(game);
  printNextFigure(game);
  printInfo(game->gameInfo);

  handleDelay(sp_start, sp_end, game->gameInfo->speed);
  
  refresh();
}

void printField(Game *game) {
  for (int i = 0; i < FIELD_HEIGHT; i++) {
    for (int j = 0; j < FIELD_WIDTH; j++) {
      int sym = game->field->blocks[i][j].block ? 2 : 1;
      attron(COLOR_PAIR(sym));
      mvaddch(i + 3, j * 2 + 2, ' ');
      mvaddch(i + 3, j * 2 + 3, ' ');
      attroff(COLOR_PAIR(sym));
    }
  }
}

void printFigure(Game *game) {
  Figure *figure = game->figure;
  for (int i = 0; i < FIGURE_HEIGHT; ++i){
    for (int j = 0; j < FIGURE_WIDTH; ++j){
      if (figure->blocks[i][j].block != 0) {
        attron(COLOR_PAIR(2));
        mvaddch(i + 3 + figure->y, j * 2 + 2 + figure->x * 2, ' ');
        mvaddch(i + 3 + figure->y, j * 2 + 3 + figure->x * 2, ' ');
        attroff(COLOR_PAIR(2));
      }
      
    }
  } 
}

void printNextFigure(Game *game) {
  for (int i = 0; i < FIGURE_HEIGHT; i++) {
    for (int j = 0; j < FIGURE_WIDTH; j++) {
      int num = game->figurest->blocks[game->gameInfo->nextID][i * FIGURE_WIDTH + j].block ? 2 : 3;
      attron(COLOR_PAIR(num));
      mvaddch(i + 5, j * 2 + 28, ' ');
      mvaddch(i + 5, j * 2 + 29, ' ');
      attroff(COLOR_PAIR(num));

    }
  }
}

void printInfo(GameInfo *gameInfo) {
  attron(COLOR_PAIR(4));
  mvwprintw(stdscr, 1, 10, "TETRIS");
  attroff(COLOR_PAIR(4));

  attron(COLOR_PAIR(3));
  mvwprintw(stdscr, 3, 26, "Next figure:");
  mvwprintw(stdscr, 11, 26, "Lvl: %d", gameInfo->level);
  mvwprintw(stdscr, 13, 26, "Speed: %d", gameInfo->speed);
  mvwprintw(stdscr, 15, 26, "Score: %d", gameInfo->score);
  mvwprintw(stdscr, 17, 26, "nextID: %d", gameInfo->nextID);
  clrtoeol();
  mvwprintw(stdscr, 17, 26, "High score: %d", gameInfo->high_score);

  if (gameInfo->pause) mvwprintw(stdscr, 12, 2, "Press ENTER to play.");
  if (gameInfo->state == GameOver) mvwprintw(stdscr, 12, 2, "      GameOver      ");
  attroff(COLOR_PAIR(3));
  attron(COLOR_PAIR(4));
  mvwprintw(stdscr, 3, 45, "Start: 'Enter'");
  mvwprintw(stdscr, 4, 45, "Pause: 'p'");
  mvwprintw(stdscr, 5, 45, "Exit: 'q'");
  mvwprintw(stdscr, 6, 45, "Arrows to move: 'a' 'd'");
  mvwprintw(stdscr, 7, 45, "Space to rotate");
  mvwprintw(stdscr, 8, 45, "Arrow down to plant: 's'");
  attroff(COLOR_PAIR(4));
}

void handleDelay(struct timespec sp_start, struct timespec sp_end,
                 int game_speed) {
  clock_gettime(CLOCK_MONOTONIC, &sp_end);
  struct timespec ts1, ts2 = {0, 0};
  if (sp_end.tv_sec - sp_start.tv_sec <= 0 &&
      (ts2.tv_nsec = (20000000 - game_speed * 1500000) -
                     (sp_end.tv_nsec - sp_start.tv_nsec)) > 0) {
    nanosleep(&ts2, &ts1);
  }
}

void getActions(Game *game) {
  char ch = getch();
  switch (ch) {
    case ' ':
      game->player->action = ROTATE;
      break;
    case 66:
      game->player->action = DOWN;
      break;
    case 67:
      game->player->action = RIGHT;
      break;
    case 68:
      game->player->action = LEFT;
      break;
    case '\n':
      game->player->action = START;
      break;
    case 'p':
      game->player->action = PAUSE;
      break;
    case 'q':
      game->player->action = TERMINATE;
      break;
    default:
      game->player->action = ACTION;
      break;
  }
}
