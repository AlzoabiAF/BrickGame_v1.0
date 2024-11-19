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
      pause(game);
    case Up:
      rotate(game);
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
  game->ticks_left--;
}

bool collision(Game *game) {
  Field *field = game->field;
  Figure *figure = game->figure; 

  for (int i = 0; i < FIGURE_HEIGHT && game->gameInfo->state != Collision; ++i)
    for (int j = 0; j < FIGURE_WIDTH && game->gameInfo->state != Collision; ++j){
        if (figure->blocks[i][j].block){
            int fx = figure->x + j;
            int fy = figure->y + i;
            if (fx < 0 || fx >= field->width || fy < 0 || fy >= field->height)
                game->gameInfo->state = Collision;

            if (field->blocks[fy][fx].block) 
                game->gameInfo->state = Collision;
        }
    }
  return game->gameInfo->state == Collision;
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

int eraseLines(Game *game) {
  Field *field = game->field;
  int count = 0;
  for (int i = FIELD_HEIGHT - 1; i >= 0; i--) {
    while (lineFilled(i, field)) {
      dropLine(i, field);
      count++;
    }
  }
  return count;
}

bool lineFilled(int i, Field *field) {
  bool flag = true  
  for (int j = 0; j < tfl->width && flag; j++)
    if (!field->blocks[i][j].block) flag = false;
  return flag;
}

void dropLine(int i, Field *field) {
  if (i == 0)
    for (int j = 0; j < FIGURE_WIDTH; j++) field->blocks[i][j].block = 0;
  else {
    for (int k = i; k > 0; k--)
      for (int j = 0; j < FIGURE_WIDTH; j++)
        field->blocks[k][j].b = field->blocks[k - 1][j].block;
  }
}

void pause(Game *game) {
  if (game->pause) {
    game->pause = 0;
    game->state = MOVING;
  } else {
    game->pause = 1;
    game->state = PAUSE;
  }
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

void rotate(Game *game) {
  if (!game->gameInfo->pause)  {
    Figure *pastFigure = game->figure;
    game->figure = rotationFigure(game);
    if (collision(game)){
        free(game->figure);
        game->figure = pastFigure;
    } else {
        free(pastFigure);
    }
  }
}

Figure *rotationFigure(Game *game) {
  Figure *figure = createFigure(game);
  figure->x = game->figure->x;
  figure->y = game->figure->y;

  for (int i = 0; i < FIGURE_HEIGHT; ++i)
    for (int j = 0; j < FIGURE_WIDTH; ++j)
      figure->blocks[i][j].b = game->figure->blocks[j][FIGURE_WIDTH - 1 - i].b;

  return figure;
}