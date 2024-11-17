#include "tetris.h"
#include "../gui/cli.h"

int main(){
    srand(time(NULL));
    initGui();
    initGame();

    freeGame();
    endwin();
}