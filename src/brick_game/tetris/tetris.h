#ifndef TETRIS_H_
#define TETRIS_H_

#include <stdbool.h>
#include <time.h>
#include <stdlib.h>

typedef enum { 
  Start, 
  Spawn,
  Reached,
  Moving, 
  Collision, 
  Pause, 
  GameOver 
} GameState;

typedef enum {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action
} UserAction;

typedef struct {
  int **field;
  int **next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} GameInfo;

typedef struct {
  int block;
} Block;


 

void initGame();
Game *createGame();
Field *createField(); 
Block **createTemplates();


#endif