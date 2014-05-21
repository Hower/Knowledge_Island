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
    int disciplines[] = {2,5 ,3,5 ,3,1,4,4 ,1,4 ,2,3,2,0,3,5,4,2 ,1};
    int dice[] =        {9,10,8,12,6,5,3,11,3,11,4,6,4,9,9,2,8,10,5};
    Game g = newGame(disciplines, dice);
    throwDice(g, 4);
    a.actionCode = BUILD_CAMPUS;
    strncpy(a.destination, "RL", PATH_LIMIT - 1);
    a.destination[PATH_LIMIT - 1] = 0;
    a.disciplineFrom = 2, a.disciplineTo = 1;
    makeAction(g, a);
    assert (getCampus(g, a.destination) == 1);
    printf("All tests passed, you are Awesome!\n");
    return EXIT_SUCCESS;
}
