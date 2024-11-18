#ifndef TETRIS_H_
#define TETRIS_H_

#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define FIELD_HEIGHT 10
#define FIELD_HEIGHT 20
#define FIGURE_WIDTH 4
#define FIGURE_HEIGHT
#define FIGURES_COUNT 7

typedef enum GameState{ 
  Start, 
  Spawn,
  Reached,
  Moving, 
  Collision, 
  Pause, 
  GameOver 
} GameState;

typedef enum UserAction{
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action
} UserAction;

typedef struct GameInfo{
  int field;
  int next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
  int ticks_left;
  int ticks;
  GameState state;
} GameInfo;

typedef struct Field {
  int width;
  int height;
  Block **blocks;
} Field;

typedef struct {
  int block;
} Block;

typedef struct Figure {
  int x;
  int y;
  int size;
  Block **blocks;
} Figure;

typedef struct FiguresT {
  int count;
  int size;
  Block **blocks;
} FiguresT;

typedef struct Player {
  int action;
} Player;

typedef struct {
  GameInfo *gameInfo;
  Field *field;
  Figure *figure;
  FiguresT *figurest;
  Player *player;
  Block **templates;
} Game;


 
// init object
Game *createGame(int field_width, int field_height, int figures_size, int count);
Field *createField(int width, int height);
Block **createTemplates();
FiguresT *createFiguresT(int count, int figures_size, Block **figures_template);
Figure *createFigure(Game *tetg);
int **createPrintField(int width, int height);
int **createNextBlock(int size);


// free object



#endif