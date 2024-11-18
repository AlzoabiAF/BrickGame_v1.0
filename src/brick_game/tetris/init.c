#include "figures.h"
#include "tetris.h"

void initGame() {
  // Game* game = createGame(10, 20, 5, 7);
  Game *game = (Game *)malloc(sizeof(Game));

  game->gameInfo =createGameInfo(10, 20, 5, 7);
  game->field = createField();
  game->templates = createTemplates();
  game->figurest = createFiguresT(count, figures_size, game->templates);
  Player *player = (Player *)malloc(sizeof(Player));
  player->action = Start;
  game->player = player;

  dropNewFigure(game);

  return game;
}

Game *createGame()

GameInfo *creatcreateGame(int field_width, int field_height, int figures_size,
                 int count) {
  


  game->gameInfo->score = 0;
  game->gameInfo->high_score = loadHighScore();
  game->gameInfo->ticks = 30;
  game->gameInfo->ticks_left = 30;
  game->gameInfo->speed = 1;
  game->gameInfo->level = 1;

  game->gameInfo->pause = 1;
  game->gameInfo->state = Start;

  game->gameInfo->next = rand() % game->figurest->count;

  return game;
}



Field *createField() {
  Field *field = (Field *)malloc(sizeof(Field));
  field->blocks = (Block **)malloc(sizeof(Block *) * height);
  for (int i = 0; i < height; i++) {
    field->blocks[i] = (Block *)malloc(sizeof(Block) * width);
    for (int j = 0; j < width; j++) {
      field->blocks[i][j].block = 0;
    }
  }

  return field;
}

Block **createTemplates() {
  Block **templates = malloc(7 * sizeof(Block *));
  templates[0] = &iFigure[0][0];
  templates[1] = &oFigure[0][0];
  templates[2] = &tFigure[0][0];
  templates[3] = &sFigure[0][0];
  templates[4] = &zFigure[0][0];
  templates[5] = &jFigure[0][0];
  templates[6] = &lFigure[0][0];
  return templates;
}

FiguresT *createFiguresT(int count, int figures_size,
                         Block **figures_template) {
  FiguresT *fieldt = (FiguresT *)malloc(sizeof(FiguresT));
  fieldt->count = count;
  fieldt->size = figures_size;
  fieldt->blocks = figures_template;

  return fieldt;
}

Figure *createFigure(Game *game) {
  Figure *figure = (Figure *)malloc(sizeof(Figure));
  figure->x = 0;
  figure->y = 0;
  figure->size = game->figurest->size;
  figure->blocks = (Block **)malloc(sizeof(Block *) * figure->size);
  for (int i = 0; i < figure->size; i++) {
    figure->blocks[i] = (Block *)malloc(sizeof(Block) * figure->size);
    for (int j = 0; j < figure->size; j++) {
      figure->blocks[i][j].block = 0;
    }
  }
  return figure;
}

int **createPrintField(int width, int height) {
  int **print_field = (int **)malloc(height * sizeof(int *));
  for (int i = 0; i < height; i++) {
    print_field[i] = (int *)malloc(width * sizeof(int));
  }

  Field *field = game->field;
  Figure *figure = game->figure;

  for (int i = 0; i < field->height; i++) {
    for (int j = 0; j < field->width; j++) {
      int sym = 0;
      if (field->blocks[i][j].block != 0)
        sym = 1;
      else {
        int x = j - figure->x;
        int y = i - figure->y;

        if (x >= 0 && x < figure->size && y >= 0 && y < figure->size)
          if (figure->blocks[y][x].block != 0) sym = 1;
      }
      print_field[i][j] = sym;
    }
  }
  return print_field;
}

int **createNextBlock(int size) {
  int **next = (int **)malloc(size * sizeof(int *));
  for (int i = 0; i < size; i++) {
    next[i] = (int *)malloc(size * sizeof(int));
    for (int j = 0; j < game->figurest->size; j++) {
      next[i][j] =
          game->templates[game->gameInfo->next][i * game->figurest->size + j].block;
    }
  }
  return next;
}

void saveHighScore(int high_score) {
  FILE *file = fopen("high_score.dat", "w");
  if (file != NULL) {
    fprintf(file, "%d", high_score);
    fclose(file);
  }
}

int loadHighScore() {
  int high_score = 0;
  FILE *file = fopen("high_score.dat", "r");
  if (file != NULL) {
    fscanf(file, "%d", &high_score);
    fclose(file);
  }
  return high_score;
}