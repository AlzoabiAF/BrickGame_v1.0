#ifndef TETRIS_H_
#define TETRIS_H_

typedef enum {
    WAITING_FOR_INPUT,
    MOVING_PIECE,
    CHECKING_LINES, 
    GAME_OVER
} statusGame;


typedef struct {
    int block;
} Block;

#endif