#ifndef CLI_H_
#define CLI_H_

#include <ncurses.h>
#include "../../brick_game/tetris/tetris.h"

void initGui();
void printGame(Game *game, struct timespec sp_start,
               struct timespec sp_end);
void printField(Game *game);
void printFigure(Game *game);
void printNextFigure(Game *game);
void printInfo(GameInfo *gameInfo);
void handleDelay(struct timespec sp_start, struct timespec sp_end,
                 int game_speed);
void getActions(Game *game);

#endif