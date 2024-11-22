#include <stdio.h>

int main(){
    int oFigure[2][4] = {{{0}, {1}, {1}, {0}}, {{0}, {1}, {1}, {0}}};

for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 4; j++) {
      printf("%d", oFigure[i][j]);
    }
    printf("\n");
  }
}