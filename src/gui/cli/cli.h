#ifndef CLI_H_
#define CLI_H_

#include <ncurses.h>
#include "../../brick_game/tetris/tetris.h"

void initGui();
void printGame(GameInfo game);
void printField(GameInfo gameInfo);
UserAction getActions();

#endif