#include "figures.h"
#include "tetris.h"

Game *initGame() {
  Game *game = (Game *)malloc(sizeof(Game));

  game->gameInfo = createGameInfo();
  game->field = createField();
  game->figure = createFigure();
  game->figurest = createFiguresT();
  game->player = createPlayer();

  dropNewFigure(game);
  game->gameInfo->nextID = rand() % FIGURES_COUNT;

  return game;
}

GameInfo *createGameInfo() {
  GameInfo *gameInfo = (GameInfo *)malloc(sizeof(GameInfo));
  gameInfo->score = 0;
  gameInfo->high_score = loadHighScore();
  gameInfo->ticks = 30;
  gameInfo->ticks_left = 30;
  gameInfo->speed = 1;
  gameInfo->level = 1;
  gameInfo->state = Start;
  gameInfo->pause = 1;
  gameInfo->nextID = rand() % FIGURES_COUNT;

  return gameInfo;
}

Field *createField() {
  Field *field = (Field *)malloc(sizeof(Field));
  field->blocks = (Block **)malloc(sizeof(Block *) * FIELD_HEIGHT);
  for (int i = 0; i < FIELD_HEIGHT; i++) {
    field->blocks[i] = (Block *)malloc(sizeof(Block) * FIELD_WIDTH);
    for (int j = 0; j < FIELD_WIDTH; j++) {
      field->blocks[i][j].block = 0;
    }
  }

  return field;
}

Figure *createFigure() {
  Figure *figure = (Figure *)malloc(sizeof(Figure));
  if (!figure) {
    return NULL; // Если память не выделена, возвращаем NULL
  }

  figure->x = 0;
  figure->y = 0;

  figure->blocks = (Block **)malloc(sizeof(Block *) * FIGURE_HEIGHT);
  if (!figure->blocks) {
    free(figure);
    return NULL; // Если память не выделена, освобождаем figure и возвращаем NULL
  }

  for (int i = 0; i < FIGURE_HEIGHT; i++) {
    figure->blocks[i] = (Block *)malloc(sizeof(Block) * FIGURE_WIDTH);
    if (!figure->blocks[i]) {
      // Если выделение памяти для строки блоков не удалось, освобождаем уже выделенные
      for (int k = 0; k < i; k++) {
        free(figure->blocks[k]);
      }
      free(figure->blocks);
      free(figure);
      return NULL;
    }

    for (int j = 0; j < FIGURE_WIDTH; j++) {
      figure->blocks[i][j].block = 0; // Инициализация блока
    }
  }

  return figure;
}

// Figure *createFigure() {
//   Figure *figure = (Figure *)malloc(sizeof(Figure));
//   figure->x = 0;
//   figure->y = 0;
//   figure->blocks = (Block **)malloc(sizeof(Block *) * FIGURE_HEIGHT);
//   for (int i = 0; i < FIGURE_HEIGHT; i++) {
//     figure->blocks[i] = (Block *)malloc(sizeof(Block) * FIGURE_WIDTH);
//     for (int j = 0; j < FIGURE_WIDTH; j++) {
//       figure->blocks[i][j].block = 0;
//     }
//   }
//   return figure;
// }

FiguresT *createFiguresT() {
  FiguresT *figurest = (FiguresT *)malloc(sizeof(FiguresT));

  Block **templates = malloc(FIGURES_COUNT * sizeof(Block *));
  templates[0] = &iFigure[0][0];
  templates[1] = &oFigure[0][0];
  templates[2] = &tFigure[0][0];
  templates[3] = &sFigure[0][0];
  templates[4] = &zFigure[0][0];
  templates[5] = &jFigure[0][0];
  templates[6] = &lFigure[0][0];

  figurest->blocks = templates;

  return figurest;
}

Player *createPlayer() {
  Player *player = (Player *)malloc(sizeof(Player));
  player->action = START;
  return player;
}

int **createPrintField(Game *game) {
  int **print_field = (int **)malloc(FIELD_HEIGHT * sizeof(int *));
  for (int i = 0; i < FIELD_HEIGHT; i++) {
    print_field[i] = (int *)malloc(FIELD_WIDTH * sizeof(int));
  }

  Field *field = game->field;
  Figure *figure = game->figure;

  for (int i = 0; i < FIGURE_HEIGHT; i++) {
    for (int j = 0; j < FIGURE_WIDTH; j++) {
      int sym = 0;
      if (field->blocks[i][j].block != 0)
        sym = 1;
      else {
        int x = j - figure->x;
        int y = i - figure->y;

        if (x >= 0 && x < FIGURE_WIDTH && y >= 0 && y < FIGURE_HEIGHT)
          if (figure->blocks[y][x].block != 0) sym = 1;
      }
      print_field[i][j] = sym;
    }
  }
  return print_field;
}

int **createNextBlock(Game *game) {
  int **next = (int **)malloc(FIGURE_HEIGHT * sizeof(int *));
  for (int i = 0; i < FIGURE_HEIGHT; i++) {
    next[i] = (int *)malloc(FIGURE_WIDTH * sizeof(int));
    for (int j = 0; j < FIGURE_WIDTH; j++) {
      next[i][j] =
          game->figurest->blocks[game->gameInfo->nextID][i * FIGURE_HEIGHT + j]
              .block;
    }
  }
  return next;
}

void saveHighScore(int high_score) {
  FILE *file = fopen("high_score.dat", "w");
  if (file) {
    fprintf(file, "%d", high_score);
    fclose(file);
  }
}

int loadHighScore() {
  int high_score = 0;
  FILE *file = fopen("high_score.dat", "r");
  if (file) {
    fscanf(file, "%d", &high_score);
    fclose(file);
  }
  return high_score;
}