#include "tetris.h"


void dropNewFigure(Game *game) {
  Figure *figure = createFigure(game);
  figure->x = FIELD_WIDTH / 2 - FIGURE_WIDTH / 2;
  figure->y = 0;

  for (int i = 0; i < FIGURE_HEIGHT; ++i) {
    for (int j = 0; j < FIGURE_WIDTH; ++j)
      figure->blocks[i][j].block =
          game->figurest->blocks[game->gameInfo->nextID][i * FIGURE_WIDTH + j]
              .block;
  }

  freeFigure(game->figure);
  game->figure = NULL;
  game->figure = figure;
  game->gameInfo->nextID = rand() % FIGURES_COUNT;
}

void calculate(Game *game) {
  if (game->gameInfo->ticks_left <= 0 && game->gameInfo->state != Pause && game->gameInfo->state != Start)
    calcOne(game);  // to slower down 30 fps game
  if (game->gameInfo->state != GameOver) {
    switch (game->player->action) {
      case PAUSE:
        pause(game);
        break;
      case ROTATE:
        rotate(game);
        break;
      case DOWN:
        down(game);
        break;
      case LEFT:
        left(game);
        break;
      case RIGHT:
        right(game);
        break;
      case TERMINATE:
        game->gameInfo->state = GameOver;
        break;
      case Start:
        game->gameInfo->pause = 0;
        game->gameInfo->state = Moving;
        break;
      default:
        break;
    }
    game->gameInfo->ticks_left--;
  }
}

void calcOne(Game *game) {
  game->gameInfo->ticks_left = game->gameInfo->ticks;
  game->gameInfo->state = Moving;
  down(game);
  if (collision(game)) {
    up(game);
    plantFigure(game);
    countScore(game);
    freeFigure(game->figure);
    dropNewFigure(game);
    game->gameInfo->state = Spawn;
    if (collision(game)) {
      game->gameInfo->state = GameOver;
    }
  }
}

bool collision(Game *game) {
  Field *field = game->field;
  Figure *figure = game->figure; 

  for (int i = 0; i < FIGURE_HEIGHT && game->gameInfo->state != Collision; ++i)
    for (int j = 0; j < FIGURE_WIDTH && game->gameInfo->state != Collision; ++j){
        if (figure->blocks[i][j].block){
            int fx = figure->x + j;
            int fy = figure->y + i;
            if (fx < 0 || fx >= FIELD_WIDTH || fy < 0 || fy >= FIELD_HEIGHT )
                game->gameInfo->state = Collision;
            else if (field->blocks[fy][fx].block)
                game->gameInfo->state = Collision;
        }
    }
  return game->gameInfo->state == Collision;
}

void plantFigure(Game *game) {
  Figure *figure = game->figure;
  for (int i = 0; i < FIGURE_HEIGHT; i++)
    for (int j = 0; j < FIGURE_WIDTH; j++)
      if (figure->blocks[i][j].block != 0) {
        int fx = figure->x + j;
        int fy = figure->y + i;
        if (fx >= 0 && fx < FIELD_WIDTH && fy >= 0 &&
            fy < FIELD_HEIGHT) {
          game->field->blocks[fy][fx].block = figure->blocks[i][j].block;
        }
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
  bool flag = true;
  for (int j = 0; j < FIELD_WIDTH && flag; ++j)
    if (!field->blocks[i][j].block) flag = false;
  return flag;
}

void dropLine(int i, Field *field) {
  if (i == 0)
    for (int j = 0; j < FIELD_WIDTH; j++) field->blocks[i][j].block = 0;
  else {
    for (int k = i; k > 0; k--)
      for (int j = 0; j < FIELD_WIDTH; j++)
        field->blocks[k][j].block = field->blocks[k - 1][j].block;
  }
}

void pause(Game *game) {
  if (game->gameInfo->pause) {
    game->gameInfo->pause = 0;
    game->gameInfo->state = Moving;
  } else {
    game->gameInfo->pause = 1;
    game->gameInfo->state = Pause;
  }
}


void up(Game *game) {
  if (!game->gameInfo->pause && !collision(game)) game->figure->y++;
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
      figure->blocks[i][j].block = game->figure->blocks[j][FIGURE_HEIGHT - 1 - i].block;

  return figure;
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
