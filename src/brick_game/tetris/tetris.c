#include "tetris.h"

#include "../../gui/cli/cli.h"

int main() {
  struct timespec sp_start, sp_end = {0, 0};
  srand(time(NULL));
  initGui();
  Game *game = initGame();

  while (game->gameInfo->state != GameOver) {
    clock_gettime(CLOCK_MONOTONIC, &sp_start);
    getActions(game);

    calculate(game);

    if (game->gameInfo->state == GameOver) {
      printGame(game, sp_start, sp_end);
    }    
  };

  freeGame(game);
  endwin();
}