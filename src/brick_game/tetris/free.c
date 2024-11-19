#include "tetris.h"

void freeGame(Game *game) {
  if (game) {
    freeFigure(game->figure);
    freeGameInfo(game->gameInfo);
    freeField(game->field);
    freeFiguresT(game->figurest);
    free(game->player);
    free(game);
  }
}

void freeGameInfo(GameInfo *gameInfo) {
  if (gameInfo) free(gameInfo);
}

void freeField(Field *field) {
  if (field) {
    for (int i = 0; i < FIELD_HEIGHT; i++) free(field->blocks[i]);
    free(field->blocks);
    free(field);
  }
}

void freeFigure(Figure *figure) {
  if (figure) {
    if (figure->blocks) {
      for (int i = 0; i < FIGURE_HEIGHT; i++) {
        if (figure->blocks[i]) {
          free(figure->blocks[i]);
        }
      }
      free(figure->blocks);
    }
    free(figure);
  }
}

void freeFiguresT(FiguresT *figureT) {
  if (figureT) free(figureT);
}

void freeNextBlock(int **next) {
  if (next) {
    for (int i = 0; i < FIGURE_HEIGHT; i++) free(next[i]);
    free(next);
  }
}
