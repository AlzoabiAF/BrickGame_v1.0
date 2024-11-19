#include "tetris.h"

void userInput(Game *game, UserAction *action, bool hold) {
  if (hold) game->player->action = action;
}

void dropNewFugure(Game *game) {
  Figure *figure = createFigure(game);
  figure->x = FIELD_WIDTH / 2 - FIGURE_WIDTH / 2;
  figure->y = 0;

  for (int i = 0; i < FIGURE_HEIGHT; ++i) {
    for (int j = 0; j < FIGURE_WIDTH; ++j)
      figure->blocks[i][j].block =
          game->figurest->blocks[game->gameInfo->nextID][i * FIGURE_HEIGHT + j]
              .block;
  }

  if (game->figure) freeFigure(game->figure);

  game->figure = figure;
  game->gameInfo->nextID = rand() % FIGURES_COUNT;
}

void calculation(Game *game) {
  // TODO: implement calculation

  // TODO: FPS
  switch (game->player->action) {
    case Pause:

    case Up:
      up(game);
    case Down:
      down(game);
    case Left:
      left(game);
    case Right:
      right(game);
    case Terminate:
      game->gameInfo->state = GameOver;
      break;
  }
  tetg->ticks_left--;
}

bool collision(Game *game) {
  // TODO: implement collision
}

int eraseLines(Game *game) {
  // TODO: implement eraseLines
}

void dropLine(Game *game) {
  // TODO: implement dropLine
}

void countScore(Game *game) {
  int erased_lines = eraseLines(game);
  switch (erased_lines) {
    case 0:
      break;
    case 1:
      game->gameInfo->score += 100;
      break;
    case 2:
      game->gameInfo->score += 300;
      break;
    case 3:
      game->gameInfo->score += 700;
      break;
    default:
      game->gameInfo->score += 1500;
      break;
  }
  if (game->gameInfo->score > game->gameInfo->high_score) {
    game->gameInfo->high_score = game->gameInfo->score;
    saveHighScore(game->gameInfo->high_score);
  }

  int new_level = game->gameInfo->score / 600 + 1;
  if (new_level > game->gameInfo->level && new_level <= 10) {
    game->gameInfo->level = new_level;
    game->gameInfo->speed = new_level;
  }
}

void pause(Game *game){
  
}

void up(Game *game) {
  if (!game->gameInfo->pause && !collision(game)) game->figure->y--;
}

void down(Game *game) {
  if (!game->gameInfo->pause && !collision(game)) game->figure->y++;
}

void left(Game *game) {
  if (!game->gameInfo->pause && !collision(game)) game->figure->x--;
}

void right(Game *game) {
  if (!game->gameInfo->pause && !collision(game)) game->figure->x++;
}
