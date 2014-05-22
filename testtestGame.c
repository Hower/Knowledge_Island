// Adley, Kevin, Mark, Keerti, Andrew
// 30/04/14
// Tests Game.c (extensively)
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "Game.h"

int main(int argc, char const *argv[]) {
    action a;
    int disciplines[] = {1,2,4,3,5,1,4,1,0,1,2,3,4,4,5,3,5,2,4};
    int dice[] = {5,2,5,3,1,5,9,12,5,7,3,11,8,1,3,9,12,8,4};
    Game g = newGame(disciplines, dice);
    throwDice(g, 5);
    a.actionCode = OBTAIN_ARC;
    strncpy(a.destination, "R", PATH_LIMIT - 1);
    a.destination[PATH_LIMIT - 1] = 0;
    a.disciplineFrom = -1217641248, a.disciplineTo = -1217641177;
    assert(isLegalAction(g, a) == TRUE);
    printf("All tests passed, you are Awesome!\n");
    return EXIT_SUCCESS;
}
