#include "tetris.h"

#include "../../gui/cli/cli.h"

int main() {
  struct timespec sp_start, sp_end = {0, 0};
  srand((unsigned int)time(NULL));
  initGui();
  Game *game = initGame();

  while (game->gameInfo->state != Quit) {
    clock_gettime(CLOCK_MONOTONIC, &sp_start);
    getActions(game);
    
    if (game->gameInfo->state != GameOver){
      calculate(game);
      printGame(game, sp_start, sp_end);
    } else {
      if (game->player->action == START){
        freeGame(game);
        game = initGame();
      }
    }
  }

  freeGame(game);
  endwin();
}