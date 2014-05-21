// Other people
// 30/04/14
// Tests Game.c (extensively)
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "Game.h"

int main(int argc, char const *argv[]) {
    // extensive testing here!
    action a;
    int disciplines[] = {1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1};
    int dice[] = {2,2,2,2,2,2,2,3,2,7,2,2,2,2,2,2,2,2,2};
    Game g = newGame(disciplines, dice);
    throwDice(g, 12);
    a.actionCode = OBTAIN_ARC;
    strncpy(a.destination, "", PATH_LIMIT - 1);
    a.destination[PATH_LIMIT - 1] = 0;
    a.disciplineFrom = 1, a.disciplineTo = 1;
    printf("All tests passed, you are Awesome!\n");
    return EXIT_SUCCESS;
}
