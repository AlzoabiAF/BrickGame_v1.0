#ifndef TETRIS_H_
#define TETRIS_H_

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define FIELD_WIDTH 10
#define FIELD_HEIGHT 20
#define FIGURE_WIDTH 4
#define FIGURE_HEIGHT 2
#define FIGURES_COUNT 7
#define TICKS 30

typedef enum GameState {
  Start,
  Spawn,
  Reached,
  Moving,
  Collision,
  Pause,
  GameOver
} GameState;

typedef enum UserAction {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action
} UserAction;

typedef struct Game {
  GameInfo *gameInfo;
  Field *field;
  Figure *figure;
  FiguresT *figurest;
  Player *player;
} Game;

typedef struct GameInfo {
  int nextID;
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
  Block **blocks;
} Field;

typedef struct Block {
  int block;
} Block;

typedef struct Figure {
  int x;
  int y;
  Block **blocks;
} Figure;

typedef struct FiguresT {
  Block **blocks;
} FiguresT;

typedef struct Player {
  int action;
} Player;

// init object
Game *initGame();
GameInfo *createGameInfo();
Field *createField();
Figure *createFigure();
FiguresT *createFiguresT(Block **figures_template);
Player *createPlayer();
int **createNextBlock(Game *game);

// free object
void freeGame(Game *game);
void freeGameInfo(GameInfo *gameInfo);
void freeField(Field *field);
void freeFigure(Figure *figure);
void freeFiguresT(FiguresT *figureT);
void freePrintField(int **print_field);
void freeNextBlock(int **next);

// highScore
void saveHighScore(int high_score);
int loadHighScore();

#endif