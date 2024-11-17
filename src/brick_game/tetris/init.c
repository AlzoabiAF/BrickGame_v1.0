#include "figures.h"
#include "tetris.h"

Game *tetg;

void initGame() {
  tetg = createGame(10, 20, 5, 7);

  Player *player = (Player *)malloc(sizeof(Player));
  player->action = Start;
  tetg->player = player;
  dropNewFigure(tetg);
}

Game *createGame(int field_width, int field_height, int figures_size,
                 int count) {
  Game *tetg = (Game *)malloc(sizeof(Game));
  tetg->field = createField(field_width, field_height);
  tetg->tet_templates = createTemplates();
  tetg->figurest = createFiguresT(count, figures_size, tetg->tet_templates);

  tetg->score = 0;
  tetg->high_score = loadHighScore();
  tetg->ticks = 30;
  tetg->ticks_left = 30;
  tetg->speed = 1;
  tetg->level = 1;

  tetg->pause = 1;
  tetg->state = INIT;

  tetg->next = rand() % tetg->figurest->count;

  return tetg;
}

Field *createField(int width, int height) {
  Field *tetf = (Field *)malloc(sizeof(Field));
  tetf->width = width;
  tetf->height = height;
  tetf->blocks = (Block **)malloc(sizeof(Block *) * height);
  for (int i = 0; i < height; i++) {
    tetf->blocks[i] = (Block *)malloc(sizeof(Block) * width);
    for (int j = 0; j < width; j++) {
      tetf->blocks[i][j].b = 0;
    }
  }

  return tetf;
}

Block **createTemplates() {
  Block **tet_templates = malloc(7 * sizeof(Block *));
  tet_templates[0] = &iFigure[0][0];
  tet_templates[1] = &oFigure[0][0];
  tet_templates[2] = &tFigure[0][0];
  tet_templates[3] = &sFigure[0][0];
  tet_templates[4] = &zFigure[0][0];
  tet_templates[5] = &jFigure[0][0];
  tet_templates[6] = &lFigure[0][0];
  return tet_templates;
}

FiguresT *createFiguresT(int count, int figures_size,
                         Block **figures_template) {
  FiguresT *tetft = (FiguresT *)malloc(sizeof(FiguresT));
  tetft->count = count;
  tetft->size = figures_size;
  tetft->blocks = figures_template;

  return tetft;
}

Figure *createFigure(Game *tetg) {
  Figure *figure = (Figure *)malloc(sizeof(Figure));
  figure->x = 0;
  figure->y = 0;
  figure->size = tetg->figurest->size;
  figure->blocks = (Block **)malloc(sizeof(Block *) * figure->size);
  for (int i = 0; i < figure->size; i++) {
    figure->blocks[i] = (Block *)malloc(sizeof(Block) * figure->size);
    for (int j = 0; j < figure->size; j++) {
      figure->blocks[i][j].b = 0;
    }
  }
  return figure;
}

int **createPrintField(int width, int height) {
  int **print_field = (int **)malloc(height * sizeof(int *));
  for (int i = 0; i < height; i++) {
    print_field[i] = (int *)malloc(width * sizeof(int));
  }

  Field *field = tetg->field;
  Figure *figure = tetg->figure;

  for (int i = 0; i < field->height; i++) {
    for (int j = 0; j < field->width; j++) {
      int sym = 0;
      if (field->blocks[i][j].b != 0)
        sym = 1;
      else {
        int x = j - figure->x;
        int y = i - figure->y;

        if (x >= 0 && x < figure->size && y >= 0 && y < figure->size)
          if (figure->blocks[y][x].b != 0) sym = 1;
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
    for (int j = 0; j < tetg->figurest->size; j++) {
      next[i][j] =
          tetg->tet_templates[tetg->next][i * tetg->figurest->size + j].b;
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